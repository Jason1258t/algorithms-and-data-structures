#include "parser.hpp"
#include <fstream>
#include <sstream>

std::ifstream Parser::openFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open places file: " + filename);
    }

    return file;
}

std::unordered_map<int, Place> Parser::parsePlacesRaw(const std::string &filename)
{
    std::ifstream file = openFile(filename);
    std::unordered_map<int, Place> places;

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        int id;
        std::string name, namePart;
        iss >> id;
        while (iss >> namePart)
            name += namePart + " ";
        name.pop_back(); // removes last space

        places[id] = {id, name, {}};
    }

    file.close();
    return places;
}

std::vector<Road> Parser::parseRoads(const std::string &filename)
{
    std::ifstream file = openFile(filename);
    std::vector<Road> roads;

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        int from, to, length;

        iss >> from >> to >> length;
        roads.push_back({from, to, length});
    }

    file.close();
    return roads;
}

std::unordered_map<int, Place> Parser::parse(const std::string &placesFile, const std::string &roadsFile)
{
    std::unordered_map<int, Place> graph = parsePlacesRaw(placesFile);
    std::vector<Road> roads = parseRoads(roadsFile);

    for (auto road : roads)
    {
        if (graph.find(road.from) == graph.end() || graph.find(road.to) == graph.end())
            continue;
        graph[road.from].roads.push_back(road);
    }

    return graph;
}