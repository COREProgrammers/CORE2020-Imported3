#include "ControlPanelSubsystem.h"

void ControlPanelSubsystem::robotInit() {}

void ControlPanelSubsystem::teleopInit() {}

void ControlPanelSubsystem::teleop() {
    /**
     * The method GetColor() returns a normalized color value from the sensor and can be
     * useful if outputting the color to an RGB LED or similar. To
     * read the raw color, use GetRawColor().
     * 
     * The color sensor works best when within a few inches from an object in
     * well lit conditions (the built in LED is a big help here!). The farther
     * an object is the more light from the surroundings will bleed into the 
     * measurements and make it difficult to accurately determine its color.
     */
    // frc::Color detectedColor = m_colorSensor.GetColor();

    /**
     * The sensor returns a raw IR value of the infrared light detected.
     */
    // double IR = m_colorSensor.GetIR();

    /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */
  //   frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  //   frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  //   frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
  //   frc::SmartDashboard::PutNumber("IR", IR);
  //   if((detectedColor.red > 0.29) & (detectedColor.green > 0.5)){
  //     frc::SmartDashboard::PutString("Color", "Yellow");
  //   }
  //   else if(detectedColor.red > 0.29){
  //     frc::SmartDashboard::PutString("Color", "Red");
  //   }
  //   else if(detectedColor.green > 0.5){
  //     frc::SmartDashboard::PutString("Color", "Green");
  //   }
  //   else if(detectedColor.blue > 0.235){
  //     frc::SmartDashboard::PutString("Color", "Blue");
  //   }

  //   uint32_t proximity = m_colorSensor.GetProximity();

  //   frc::SmartDashboard::PutNumber("Proximity", proximity);
  // }
}
