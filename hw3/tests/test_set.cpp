#include <gtest/gtest.h>
#include "set.h"
#include <iostream>
#include <algorithm>


TEST(Set, InitializerList) {
    const auto stl_set = std::set<float>{1, 2, 3, 9, 0};
    auto set = hw3::Set<float>{1, 2, 3, 9, 0};
    set.insert(3);
    std::ranges::for_each(stl_set, [](const auto &el) { std::cout << el << ' '; });
    std::cout << '\n';
    std::cout << *stl_set.lower_bound(4) << '\n';
    std::cout << *stl_set.upper_bound(8.5) << '\n';
    std::cout << set.lower_bound(4)->getKey() << '\n';
    std::cout << set.upper_bound(8.5)->getKey() << '\n';
    set.erase(3);
    auto *el = set.begin();
    while (el != nullptr) {
        std::cout << el->getKey() << ' ';
        el = el->next();
    }
}
