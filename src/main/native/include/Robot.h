#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/geometry/Pose2d.h>

#include <networktables/NetworkTable.h>

#include "utils/FileLogger.h"
#include "Loggers.h"

#include <functional>
#include <iostream>
#include <vector>

namespace numbat {
namespace robot {
class NumbatRobot {
    public:
        NumbatRobot(frc::TimedRobot *robot, std::vector<loggers::Logger*> loggers);
        NumbatRobot(frc::TimedRobot *robot);
        NumbatRobot();

        void Log();
        void AddLogger(loggers::Logger *logger);
        void SetPosition(frc::Pose2d position);

    private:
        void INIT_FILE();
        void INIT_TIMER();

        frc::TimedRobot *_robot;
        std::vector<loggers::Logger*> _loggers;
        numbat::utils::LogFile _logFile;
        frc::Timer _timer;

        frc::Pose2d _position;
};

}
}