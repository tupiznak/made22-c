#include <gtest/gtest.h>
#include "set_iterator.h"
#include <iostream>
#include <algorithm>


TEST(SetIterator, Basic) {
    {
        auto stl_set = std::set<float>{1, 2, 0, 3, 2};
        std::set<float>::iterator stl_it;
        std::cout << "2\n";
        static_assert(std::bidirectional_iterator<std::set<float>::iterator>);
        static_assert(std::bidirectional_iterator<hw3::SetIterator<float>>);
    }
//    {
//        const int arr[] = {1, 2, 3, 5, 2, 0};
//        auto begin = hw3::SetIterator<int>{arr};
//        auto end = hw3::SetIterator<int>{&arr[6]};
//        std::for_each(begin, end, [](const auto &el) { std::cout << el << ", "; });
//        std::cout << '\n';
//    }
//    {
//        const int arr[] = {1, 2, 3, 5, 2, 0};
//        const auto ptr = &arr;
//        auto begin = hw3::SetIterator<int>{ptr};
//        auto end = hw3::SetIterator<int>{&arr[6]};
//        std::for_each(begin, end, [](const auto &el) { std::cout << el << ", "; });
//        std::cout << '\n';
//    }
}
