#include "IntakeSubsystem.h"

IntakeSubsystem::IntakeSubsystem() : m_intakeMotor(INTAKE_PORT), 
                                     m_intakeSolenoid(LEFT_DRIVE_SHIFTER_PCM, frc::PneumaticsModuleType::CTREPCM, INTAKE_DOWN_PORT, INTAKE_UP_PORT),
                                     m_intakeSpeed("Intake Speed", 0){
}

void IntakeSubsystem::robotInit(){
    m_intakeMotor.Set(ControlMode::PercentOutput, 0);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
    m_isIntakeDown = false;
}

void IntakeSubsystem::teleopInit() {}

void IntakeSubsystem::teleop(){
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)){
       SetIntake(-m_intakeSpeed.Get());
    }
    else{
       SetIntake(0.0);
    }
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        SetIntake(m_intakeSpeed.Get());
    }
}

void IntakeSubsystem::SetIntake(double intakeSpeed) {
   m_intakeMotor.Set(ControlMode::PercentOutput, intakeSpeed); 
}
void IntakeSubsystem::ToggleIntake() {
    if(m_isIntakeDown) {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::kForward);
    } else {
        m_intakeSolenoid.Set(frc::DoubleSolenoid::kReverse);
    }
}
