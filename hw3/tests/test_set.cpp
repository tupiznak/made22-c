#include <gtest/gtest.h>
#include "set.h"
#include <iostream>
#include <algorithm>


TEST(Set, InitializerList) {
    auto const stl_set = std::set<int>{1, 2, 3, 9, 0};
    [[maybe_unused]] auto const set = hw3::Set<int>{1, 2, 3, 9, 0};
    std::ranges::for_each(stl_set, [](const auto &el) { std::cout << el << ' '; });
    std::cout << '\n';
}
