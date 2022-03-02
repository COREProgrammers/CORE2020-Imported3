#pragma once

// #include <rev/ColorSensorV3.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <CORERobotLib.h>

using namespace CORE;

class ControlPanelSubsystem : public CORESubsystem {
public:
    ControlPanelSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
private:
    // rev::ColorSensorV3 m_colorSensor{i2cPort};
};