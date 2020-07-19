#include "../include/LogCmd.hpp"
#define LOG(prefix, message) std::cout << prefix << message << std::endl;

namespace logcmd {

    void info(const char* message)
    {
        LOG("[INFO]: ", message)
    };

    void warn(const char* message)
    {
        LOG("[WARNING]: ", message)
    };

    void err(const char* message)
    {
        LOG("[ERROR]: ", message)
    };

}
