// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "Robot.h"

#include <iostream>

robot::NumbatRobot::NumbatRobot(frc::TimedRobot* robot,
                                std::vector<loggers::Logger*> loggers)
    : _robot(robot), _loggers(loggers) {
  INIT_FILE();
  INIT_TIMER();
}

robot::NumbatRobot::NumbatRobot(frc::TimedRobot* robot) : _robot(robot) {
  INIT_FILE();
  INIT_TIMER();
}

robot::NumbatRobot::NumbatRobot() : _robot(nullptr) {
  INIT_FILE();
  INIT_TIMER();
}

void robot::NumbatRobot::INIT_TIMER() {
  _timer.Start();
}

void robot::NumbatRobot::Log() {
  for (loggers::Logger* logger : _loggers) {
    logger->OnLogTick();
    std::string name = logger->GetName();
  }
}

void robot::NumbatRobot::SetPosition(frc::Pose2d position) {
  _logFile._data["positions"][_timer.Get().value()] = position;
}

void robot::NumbatRobot::AddLogger(loggers::Logger* logger) {
  _loggers.push_back(logger);
}

void robot::NumbatRobot::INIT_FILE() {
  _logFile = utils::LogFile("log.txt");
}
