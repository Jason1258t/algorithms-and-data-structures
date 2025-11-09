#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include "way.hpp"

#include <set>

std::pair<int, int> findTwoSmallest(int a, int b, int c, int d)
{
    auto nums = prepareNums(a, b, c, d);

    std::partial_sort(nums.begin(), nums.begin() + 2, nums.end());
    return {nums[0], nums[1]};
}

std::pair<int, int> findTwoSmallest(Way way1, Way way2)
{
    auto nums = prepareNums(way1.shortest, way1.alternative, way2.shortest, way2.alternative);

    std::partial_sort(nums.begin(), nums.begin() + 2, nums.end());
    return {nums[0], nums[1]};
}

std::vector<int> prepareNums(int a, int b, int c, int d)
{
    std::set<int> unique_nums = {a, b, c, d};
    std::vector<int> nums(unique_nums.begin(), unique_nums.end());

    if (nums.size() < 2)
    {
        nums.resize(2, std::numeric_limits<int>::max());
    }
}