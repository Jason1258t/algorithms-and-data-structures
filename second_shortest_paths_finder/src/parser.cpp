#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::ifstream Parser::openFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    return file;
}

std::unordered_map<int, Place> Parser::parse(const std::string &filename)
{
    std::ifstream file = openFile(filename);
    std::unordered_map<int, Place> graph;
    
    std::string line;
    
    if (!std::getline(file, line) || line.empty())
    {
        throw std::runtime_error("Invalid file format: missing first line");
    }
    
    std::istringstream firstLineIss(line);
    int numVertices, numRoads;
    firstLineIss >> numVertices >> numRoads;
    
    for (int i = 1; i <= numVertices; ++i)
    {
        graph[i] = {i, std::to_string(i), {}};
    }
    
    for (int i = 0; i < numRoads; ++i)
    {
        if (!std::getline(file, line) || line.empty())
        {
            throw std::runtime_error("Invalid file format: missing road data");
        }
        
        std::istringstream iss(line);
        int from, to, length;
        
        iss >> from >> to >> length;
        
        if (graph.find(from) != graph.end() && graph.find(to) != graph.end())
        {
            graph[from].roads.push_back({from, to, length});
        }
    }
    
    file.close();
    return graph;
}