#include "ConveyorSubsystem.h"

using namespace CORE;

ConveyorSubsystem::ConveyorSubsystem() : m_lowerConveyorMotor(CONVEYOR_1_PORT),
                                         m_frontConveyorMotor(CONVEYOR_2_PORT),
                                         m_backConveyorMotor(CONVEYOR_3_PORT),
                                         m_lowerConveyorSpeed("Lower Conveyor Speed", 0),
                                         m_upperConveyorSpeed("Upper Conveyor Speed", 0) {
}

void ConveyorSubsystem::robotInit(){
    m_lowerConveyorMotor.Set(ControlMode::PercentOutput, 0);
    m_frontConveyorMotor.Set(ControlMode::PercentOutput, 0);
    m_backConveyorMotor.Set(ControlMode::PercentOutput, 0);
    m_lowerConveyorMotor.SetInverted(true);
    m_frontConveyorMotor.SetInverted(false);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON);
}

void ConveyorSubsystem::teleopInit() {}

void ConveyorSubsystem::teleop(){
    if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
        setMotor(m_lowerConveyorSpeed.Get(), m_upperConveyorSpeed.Get());
    } else if(operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::RIGHT_BUTTON)) {
        setMotor(-m_lowerConveyorSpeed.Get(), -m_upperConveyorSpeed.Get());
    } else {
        setMotor(0.0, 0.0);
    }
}

void ConveyorSubsystem::setMotor(double lowerConveyorSpeed, double upperConveyorSpeed){
    m_lowerConveyorMotor.Set(ControlMode::PercentOutput, lowerConveyorSpeed); 
    m_frontConveyorMotor.Set(ControlMode::PercentOutput, upperConveyorSpeed);
    m_backConveyorMotor.Set(ControlMode::PercentOutput, upperConveyorSpeed);
}
