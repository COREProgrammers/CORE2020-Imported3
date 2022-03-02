#pragma once

#include <frc/DoubleSolenoid.h>
#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;
using namespace frc;

class ClimberSubsystem : public CORESubsystem {
public:
    ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void climberMove(bool m_climberExtended);

private:
    bool m_climberExtended;
    DoubleSolenoid m_climberSolnoidOne, m_climberSolnoidTwo;
};
