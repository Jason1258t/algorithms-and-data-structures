#pragma once

#include "place.hpp"
#include "way.hpp"
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <climits>

void printDetailedWays(const std::unordered_map<int, Way> &ways,
                       const std::unordered_map<int, Place> &graph)
{
    std::cout << "\n =====  ДОРОГИ  ===== \n";
    std::cout << "═══════════════════════════════════════\n";

    for (const auto &[key, way] : ways)
    {
        auto fromIt = graph.find(way.from);
        auto toIt = graph.find(way.to);

        std::string fromName = (fromIt != graph.end()) ? fromIt->second.name : "Неизвестно";
        std::string toName = (toIt != graph.end()) ? toIt->second.name : "Неизвестно";

        auto alternativeWayValue = way.alternative != INT_MAX ? std::to_string(way.alternative) : "infinity";

        std::cout << "📍 Маршрут: " << fromName << " → " << toName << "\n";
        std::cout << "   ├─ Самый короткий путь: " << std::setw(4) << way.shortest << "\n";
        std::cout << "   └─ Альтернативный путь: " << std::setw(4) << alternativeWayValue << "\n";
        std::cout << std::endl;
    }
}