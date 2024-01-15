#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>

#include <functional>
#include <iostream>

namespace numbat {
namespace utils {

  class RobotStartup {
   public:
    static void Start(std::function<int()> func);
  };

  template <class RobotClass>
  int StartRobot() {
    RobotStartup::Start(frc::StartRobot<RobotClass>);
    return 0;
  }

#ifndef RUNNING_FRC_TESTS
#define NUMBAT_ROBOT_MAIN(RobotClz)     \
  int main() {                          \
    wom::utils::StartRobot<RobotClz>(); \
  }
#else
#define NUMBAT_ROBOT_MAIN(RobotClz)
#endif
}
}