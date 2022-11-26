#include <gtest/gtest.h>
#include "set.h"
#include <iostream>
#include <algorithm>


TEST(Set, InitializerList) {
    const auto stl_set = std::set<int>{1, 2, 3, 9, 0};
    [[maybe_unused]] auto set = hw3::Set<int>{1, 2, 3, 9, 0};
    set.insert(3);
    std::ranges::for_each(stl_set, [](const auto &el) { std::cout << el << ' '; });
    std::cout << '\n';
}
