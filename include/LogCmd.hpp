#pragma once
#include <iostream>

namespace logcmd {
    void log(std::string prefix, std::string content);
    void info(std::string content);
    void warn(std::string content);
    void err(std::string content);
} // End logcmd
