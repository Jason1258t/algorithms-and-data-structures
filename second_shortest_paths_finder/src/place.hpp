#pragma once

#include <string>
#include <vector>
#include "road.hpp"

struct Place
{
    int id;
    std::string name;
    std::vector<Road> roads; // дороги, выходящие из точки
};
