#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "parser.hpp"
#include "way.hpp"
#include "print.hpp"
#include "utils.hpp"
#include <climits>

// Домогацкий Иван ПС-22

// Среда выполнения:
// Apple clang version 16.0.0 (clang-1600.0.26.3)
// Target: arm64-apple-darwin24.6.0
// Thread model: posix

// 26. Имеется сеть автомобильных дорог. По  некоторым дорогам
// можно  проехать  только  в одном  направлении. Известна  длина
// каждой дороги, причем она может быть разной в  зависимости  от
// направления. Один  из  городов  является  столицей.  Требуется
// вывести список длин вторых по минимальности путей из столицы в
// другие города. Допускается присутствие циклических путей (12).

Way createNewWay(Way startWay, Road road)
{
    Way way = {startWay.from, road.to, startWay.shortest + road.length, startWay.alternative + road.length};
    if (startWay.alternative == INT_MAX || startWay.shortest == startWay.alternative)
    {
        way.alternative = INT_MAX;
    }
}

int main(int argc, char *argv[])
{
    std::string placesFilename;
    std::string roadsFilename;
    int start;
    if (argc == 4)
    {
        start = std::stoi(argv[1]);
        placesFilename = argv[2];
        roadsFilename = argv[3];
    }
    else
    {
        std::cout << "Enter place filename: ";
        std::cin >> placesFilename;

        std::cout << "Enter roads filenmae: ";
        std::cin >> roadsFilename;

        std::cout << "Enter start place id: ";
        std::cin >> start;
    }

    std::unordered_map<int, Place> graph = Parser::parse(placesFilename, roadsFilename);
    std::unordered_map<int, Way> ways;
    ways[start] = {start, start, 0, 0};

    std::queue<Place> queue;
    queue.push(graph[start]);

    while (!queue.empty())
    {
        Place place = queue.front();
        queue.pop();

        for (auto road : place.roads)
        {
            bool addToQueue = false;

            Way way = createNewWay(ways[road.from], road);

            if (ways.find(road.to) == ways.end())
            {
                ways[road.to] = way;
                addToQueue = true;
            }

            Way &currentWay = ways[road.to];
            auto shortestWays = findTwoSmallest(currentWay, way);

            if (shortestWays.first != currentWay.shortest || shortestWays.second != currentWay.alternative)
            {
                currentWay.shortest = shortestWays.first;
                currentWay.alternative = shortestWays.second;
                addToQueue = true;
            }
            if (addToQueue)
            {
                queue.push(graph[road.to]);
            }
        }
    }

    printDetailedWays(ways, graph);
}