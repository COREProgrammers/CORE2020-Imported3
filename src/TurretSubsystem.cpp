#include "TurretSubsystem.h"

TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT),
                                    m_KP("KP", 0.0005),
                                    m_KI("KI", 0),
                                    m_KD("KD", 0),
                                    m_KF("KF", 1),
                                    m_DistCoefA("DistCoefA", 0),
                                    m_DistCoefB("DistCoefB", 0),
                                    m_DistCoefC("DistCoefC", 0),
                                    m_DistCoefD("DistCoefD", 0),
                                    corePID(0, 0, 0, 0) {
    std::cout << "Turret Subsystem constructer called" << std::endl;
}

void TurretSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::BACK_BUTTON);
    operatorJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_X);
    InitTalons();
    // start NetworkTables
    ntinst = nt::NetworkTableInstance::GetDefault();
    ntinst.StartClientTeam(2062);


}

void TurretSubsystem::teleopInit() {
    m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
}

void TurretSubsystem::teleop() {
    double manualInput = -operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X);
    bool backButtonPressed = operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::BACK_BUTTON);
    double motorPercent = 0;
    bool atLeftStop = m_turret.GetSelectedSensorPosition(0) < (m_startupTurretPosition - 7000.0);
    bool atRightStop = m_turret.GetSelectedSensorPosition(0) > (m_startupTurretPosition + 7000.0);

    if (backButtonPressed) {
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode",3);
        nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode",0);
        motorPercent = CalculateMotorFromVision(atLeftStop, atRightStop);
    } else if ((!atRightStop && manualInput < 0) || (!atLeftStop && manualInput > 0)) {
         nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode",1);
         nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode",1);
        // manual turret position
        motorPercent = 0.25 * manualInput;
    }
    SetTurret(motorPercent);

    SmartDashboard::PutNumber("Distance from target", GetDistance());
    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
    SmartDashboard::PutBoolean("At Left Stop", atLeftStop);
    SmartDashboard::PutBoolean("At Right Stop", atRightStop);
    SmartDashboard::PutBoolean("BACK Button Pressed", operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::BACK_BUTTON));
}

double TurretSubsystem::CalculateMotorFromVision(bool atLeftStop, bool atRightStop) {
    // auto turret position
    corePID.SetDerivativeConstant(m_KD.Get());
    corePID.SetFeedForwardConstant(m_KF.Get());
    corePID.SetIntegralConstant(m_KI.Get());
    corePID.SetProportionalConstant(m_KP.Get());
    auto table = ntinst.GetTable("limelight");
    bool hasCenterX = table->GetNumber("tv", 0.0) == 1;
    double conversion = 4096 / -360; // convert degrees to ticks
    // calculate center error as a percent output for the motor
    double centerError = table->GetNumber("tx", 0.0) * conversion;

    SmartDashboard::PutNumber("Center Error", centerError);
    SmartDashboard::PutBoolean("HasTable", hasCenterX);

    if (hasCenterX && ((!atRightStop && centerError < 0) || (!atLeftStop && centerError > 0))) {
        return corePID.Calculate(centerError);
    } else {
        return 0;
    }
}

double TurretSubsystem::GetDistance() {
    auto table = ntinst.GetTable("limelight");
    double x = table->GetNumber("thor", 0.0);
    double a = m_DistCoefA.Get(), b = m_DistCoefB.Get(), c = m_DistCoefC.Get(), d = m_DistCoefD.Get();
    //double distance = a * (x * x * x) + b * (x * x) + c * x + d;
    double distance = a * pow(x, b);
    return distance;
}

void TurretSubsystem::InitTalons() {
	// Sets up talons
	m_turret.Set(ControlMode::PercentOutput, 0);
    // Zero the sensor
    m_turret.SetSelectedSensorPosition(0, 0, 10);
    m_turret.SetInverted(true);
}

void TurretSubsystem::SetTurret(double turretPercent) {
    m_turret.Set(ControlMode::PercentOutput, turretPercent);
}
