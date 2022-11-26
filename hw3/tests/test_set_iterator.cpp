#include <gtest/gtest.h>
#include "set_iterator.h"
#include <iostream>
#include <algorithm>

TEST(SetIterator, Basic) {
    {
        auto stl_set = std::set<float>{1, 2, 0, 3, 2};
        std::set<float>::iterator stl_it;
        static_assert(std::bidirectional_iterator<std::set<float>::iterator>);
        static_assert(std::bidirectional_iterator<hw3::SetIterator<float>>);
    }
    {
        const int arr[] = {1, 2, 3, 5, 2, 0};
        auto begin = hw3::SetIterator<int>{arr};
        auto end = hw3::SetIterator<int>{&arr[6]};
        ASSERT_EQ(true, std::equal(begin, end, arr));
//        std::ranges::for_each(begin, end, [](const auto &el) { std::cout << el << ", "; });
//        std::cout << '\n';
    }
    {
        const int arr[] = {1, 2, 3, 5, 2, 0};
        const auto ptr = &arr;
        auto begin = hw3::SetIterator<int>{*ptr};
        auto end = hw3::SetIterator<int>{*ptr + 6};
        ASSERT_EQ(true, std::equal(begin, end, arr));
    }
    {
        const int arr[] = {1, 2, 3, 5, 2, 0};
        const int arr_reverse[] = {0, 2, 5, 3, 2, 1};
        const auto ptr = &arr;
        auto begin = hw3::SetIterator<int>{*ptr};
        auto end = hw3::SetIterator<int>{*ptr + 6};

        auto vec_test = std::vector<float>{1, 2, 0, 3, 2, 43};
        auto vec = std::vector<float>(vec_test.begin(), vec_test.end());
        ASSERT_EQ(true, std::equal(vec.begin(), vec.end(), vec_test.begin()));

        std::ranges::copy(begin, end, vec.begin());
        ASSERT_EQ(true, std::equal(vec.begin(), vec.end(), arr));

        std::ranges::reverse_copy(begin, end, vec.begin());
        ASSERT_EQ(true, std::equal(vec.begin(), vec.end(), arr_reverse));
    }
}
