#pragma once
#include <stdexcept>
#include <string>

class ParserError : public std::runtime_error
{
private:
    int exitCode;

public:
    ParserError(const std::string& message, int code = 11)
        : std::runtime_error(message), exitCode(code) {}

    int getExitCode() const { return exitCode; }
};