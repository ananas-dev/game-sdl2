#include "LogCmd.hpp"

namespace logcmd {

    void log(std::string prefix, std::string something)
    {
        std::cout << prefix << something << std::endl;
    }

    void info(std::string something)
    {
        log("[INFO]: ", something);
    }

    void warn(std::string something)
    {
        log("[WARNING]: ", something);
    }

    void err(std::string something)
    {
        log("[ERROR]: ", something);
    }

}
