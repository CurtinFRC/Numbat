#include <string>

#include <wpi/json.h>

#include <fstream>
#include <iostream>

namespace numbat {
namespace utils {
class LogFile {
    public:
        LogFile(std::string path);
        LogFile();
        void UpdateData(std::string key, std::string value);
        void Write();
        void Close();

        wpi::json _data;
    private:
        std::string _path;
        std::ofstream _file;
};
}
}