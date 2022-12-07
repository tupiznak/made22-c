#include <gtest/gtest.h>
#include "set.h"
#include <random>


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
    std::ranges::for_each(set, [](const auto &el) { std::cout << el << ' '; });
    EXPECT_EQ(true, std::ranges::equal(set, stl_set));
    set.erase(3);
}

TEST(Set, EqSTL) {
    std::mt19937 gen(0);
    std::uniform_real_distribution<> dis(-100, 500);
    const auto stl_set = [&]() {
        std::array<int, 300> arr;
        std::set<int> stl_set;
        for (auto &el: arr) { stl_set.insert(dis(gen)); }
        return stl_set;
    }();

    auto set = hw3::Set<int>(stl_set.begin(), stl_set.end());
    EXPECT_EQ(true, std::ranges::equal(set, stl_set));
}
