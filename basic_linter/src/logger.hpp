#pragma once

#include <ostream>
#include <string>

enum class LoggerMode
{
    normal, 
    debug
};

class Logger
{
private:
    LoggerMode mode;
    std::ostream& out;  

public:
    Logger(std::ostream& ostream, LoggerMode loggerMode = LoggerMode::normal)
        : mode{loggerMode}, out{ostream} {}

    void print(const std::string &message)
    {
        out << message << '\n';
    }
    
    void log(const std::string &message)
    {
        if (mode != LoggerMode::debug)
            return;
        print(message);
    }
};