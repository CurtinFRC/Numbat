// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#pragma once

#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/geometry/Pose2d.h>
#include <networktables/NetworkTable.h>

#include <functional>
#include <iostream>
#include <vector>

#include "Loggers.h"
#include "utils/FileLogger.h"

namespace robot {
class NumbatRobot {
 public:
  NumbatRobot(frc::TimedRobot* robot, std::vector<loggers::Logger*> loggers);
  explicit NumbatRobot(frc::TimedRobot* robot);
  NumbatRobot();

  void Log();
  void AddLogger(loggers::Logger* logger);
  void SetPosition(frc::Pose2d position);

 private:
  void INIT_FILE();
  void INIT_TIMER();

  frc::TimedRobot* _robot;
  std::vector<loggers::Logger*> _loggers;
  utils::LogFile _logFile;
  frc::Timer _timer;

  frc::Pose2d _position;
};

}  // namespace robot
