#include <string>
#include <vector>
#include <unordered_map>
#include "place.hpp"

class Parser
{
public:
    static std::unordered_map<int, Place> parse(const std::string &placesFile, const std::string &roadsFile);
private:
    static std::vector<Road> parseRoads(const std::string &roadsFile);
    static std::unordered_map<int, Place> parsePlacesRaw(const std::string &placesFile);
    static std::ifstream openFile(const std::string &filename);
};