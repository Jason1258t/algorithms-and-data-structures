#pragma once

#include <unordered_map>
#include "way.hpp"
#include "place.hpp"
#include <set>

class PathFinder
{
public:
    static std::unordered_map<int, Way> findWays(std::unordered_map<int, Place> graph, int start);

private:
    static Way createNewWay(Way startWay, Road road);

    static std::pair<int, int> findTwoSmallest(Way way1, Way way2)
    {
        std::set<int> unique_nums = {way1.shortest, way1.alternative, way2.shortest, way2.alternative};
        std::vector<int> nums(unique_nums.begin(), unique_nums.end());

        if (nums.size() < 2)
        {
            nums.resize(2, std::numeric_limits<int>::max());
        }

        std::partial_sort(nums.begin(), nums.begin() + 2, nums.end());
        return {nums[0], nums[1]};
    }
};