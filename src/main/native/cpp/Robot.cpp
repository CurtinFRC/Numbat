#include "Robot.h"

#include <iostream>

numbat::robot::NumbatRobot::NumbatRobot(frc::TimedRobot *robot, std::vector<loggers::Logger*> loggers) : _robot(robot), _loggers(loggers) {
  INIT_FILE();
  INIT_TIMER();
}

numbat::robot::NumbatRobot::NumbatRobot(frc::TimedRobot *robot) : _robot(robot) {
  INIT_FILE();
  INIT_TIMER();
}

numbat::robot::NumbatRobot::NumbatRobot() : _robot(nullptr) {
  INIT_FILE();
  INIT_TIMER();
}

void numbat::robot::NumbatRobot::INIT_TIMER() {
  _timer.Start();
}

void numbat::robot::NumbatRobot::Log() {
  for (loggers::Logger *logger : _loggers) {
    logger->OnLogTick();
    std::string name = logger->GetName();
  }
}

void numbat::robot::NumbatRobot::SetPosition(frc::Pose2d position) {
  _logFile._data["positions"][_timer.Get().value()] = position;
}

void numbat::robot::NumbatRobot::AddLogger(loggers::Logger *logger) {
  _loggers.push_back(logger);
}

void numbat::robot::NumbatRobot::INIT_FILE() {
  _logFile = numbat::utils::LogFile("log.txt");
}