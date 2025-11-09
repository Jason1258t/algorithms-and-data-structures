#include "path_finder.hpp"
#include <queue>

Way PathFinder::createNewWay(Way startWay, Road road)
{
    Way way = {startWay.from, road.to, startWay.shortest + road.length, startWay.alternative + road.length};
    if (startWay.alternative == INT_MAX || startWay.shortest == startWay.alternative)
    {
        way.alternative = INT_MAX;
    }
    return way;
}

std::unordered_map<int, Way> PathFinder::findWays(std::unordered_map<int, Place> graph, int start)
{
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

    return ways;
}