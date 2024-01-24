// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include "Robot.h"

#include <iostream>

robot::NumbatRobot::NumbatRobot(frc::TimedRobot* robot, std::vector<loggers::Logger*> loggers,
                                loggers::LimelightLogger* limelightLogger)
    : _robot(robot), _loggers(loggers), _limelight(limelightLogger) {
  INIT_FILE();
  INIT_TIMER();
}

robot::NumbatRobot::NumbatRobot(frc::TimedRobot* robot, loggers::LimelightLogger* limelightLogger)
    : _robot(robot), _limelight(limelightLogger) {
  INIT_FILE();
  INIT_TIMER();
}

robot::NumbatRobot::NumbatRobot(frc::TimedRobot* robot, std::vector<loggers::Logger*> loggers)
    : _robot(robot), _loggers(loggers), _limelight(nullptr) {
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
    std::vector<std::pair<std::string, double>> data = logger->OnLogTick();
    std::string name = logger->GetName();

    _logFile._data[name][_timer.Get().value()] = data;
  }

  if (_limelight != nullptr) {
    _logFile._data["limelight"][_limelight->GetName()][_timer.Get().value()] = _limelight->OnLogTick();
  }

  // _logFile.Write();
  std::cout << _logFile._data.dump(2) << std::endl;
}

void robot::NumbatRobot::SetPosition(frc::Pose2d position) {
  _logFile._data["positions"][_timer.Get().value()] = position;
}

void robot::NumbatRobot::AddLogger(loggers::Logger* logger) {
  _loggers.push_back(logger);
}

void robot::NumbatRobot::SetLimelight(loggers::LimelightLogger* limelight) {
  _limelight = limelight;
}

void robot::NumbatRobot::INIT_FILE() {
  _logFile = utils::LogFile("log.txt");
}
