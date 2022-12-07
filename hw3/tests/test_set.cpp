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
    set.erase(5);
    EXPECT_EQ(5, set.size());

    EXPECT_EQ(set.end(), set.find(5));
    EXPECT_EQ(set.find(9), ++set.find(3));
    EXPECT_EQ(set.find(2), --set.find(3));
}

TEST(Set, EqSTLInit) {
    std::mt19937 gen(0);
    std::uniform_real_distribution<> dis(-100, 500);
    const auto stl_set = [&]() {
        std::set<int> stl_set;
        for ([[maybe_unused]] int i: std::views::iota(0, 300)) { stl_set.insert(dis(gen)); }
        return stl_set;
    }();

    const auto set = hw3::Set<int>(stl_set.begin(), stl_set.end());
    EXPECT_EQ(true, std::ranges::equal(set, stl_set));
}

TEST(Set, EqSTLErase) {
    std::mt19937 gen(1);
    std::uniform_real_distribution<> dis(-100, 500);

    std::set<int> stl_set;
    hw3::Set<int> set;
    EXPECT_EQ(true, set.empty());

    for ([[maybe_unused]] int i: std::views::iota(0, 300)) {
        const auto el = dis(gen);
        stl_set.insert(el);
        set.insert(el);
    }

    EXPECT_EQ(true, std::ranges::equal(set, stl_set));
    EXPECT_EQ(stl_set.size(), set.size());

    for ([[maybe_unused]] int i: std::views::iota(0, 300)) {
        const auto el = dis(gen);
        stl_set.erase(el);
        set.erase(el);
    }

    EXPECT_EQ(true, std::ranges::equal(set, stl_set));
    EXPECT_EQ(stl_set.size(), set.size());
    EXPECT_EQ(false, set.empty());
}
