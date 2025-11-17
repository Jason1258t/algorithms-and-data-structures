#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "place.hpp"

class Parser
{
public:
    static std::unordered_map<int, Place> parse(const std::string &filename);
private:
    static std::ifstream openFile(const std::string &filename);
};