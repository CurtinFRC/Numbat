// Copyright (c) 2023-2024 CurtinFRC
// Open Source Software, you can modify it according to the terms
// of the MIT License at the root of this project

#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>

#include <functional>
#include <iostream>

namespace robot {

class RobotStartup {
 public:
  static void Start(std::function<int()> func);
};

template <class RobotClass>
int StartRobot() {
  RobotStartup::Start(frc::StartRobot<RobotClass>);
  return 0;
}

#ifndef NUMBAT_SRC_MAIN_NATIVE_INCLUDE_UTILS_ROBOTSTARTUP_H_
#define NUMBAT_SRC_MAIN_NATIVE_INCLUDE_UTILS_ROBOTSTARTUP_H_(RobotClz) \
  int main() {                                                         \
    numbat::StartRobot<RobotClz>();                                    \
  }
#else
#define NUMBAT_ROBOT_MAIN(RobotClz)
#endif  // NUMBAT_SRC_MAIN_NATIVE_INCLUDE_UTILS_ROBOTSTARTUP_H_
}  // namespace robot
