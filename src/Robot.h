#pragma once

#include <string>
#include <iostream>
#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <CORERobotLib.h>
#include <COREFramework/COREScheduler.h>
#include "ClimberSubsystem.h"
#include "ControlPanelSubsystem.h"
#include "ConveyorSubsystem.h"
#include "DriveSubsystem.h"
#include "IntakeSubsystem.h"
#include "LauncherSubsystem.h"
#include "TurretSubsystem.h"
#include "Config.h"

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public: 
 	Robot();
	void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void test() override;
	void testInit() override;
	static Robot * GetInstance();
	DriveSubsystem driveSubsystem;
	LauncherSubsystem launcherSubsystem;
	IntakeSubsystem intakeSubsystem;
	TurretSubsystem turretSubsystem;
	ConveyorSubsystem conveyorSubsystem;

private:
	static Robot * m_instance;
};
