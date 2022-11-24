#ifndef MADE22_C_SET_H
#define MADE22_C_SET_H

#include <functional>
#include <algorithm>
#include <iostream>

#include "set_iterator.h"

namespace hw3 {
    template<class T>
    class Set {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = std::initializer_list<T>;
        using const_iterator = std::initializer_list<T>;
        using size_type = size_t;
        using pointer = T *;
        using const_pointer = const T *;

        Set() = default;

        Set(std::initializer_list<value_type> init);

//        SetIterator<reference> begin() { return Iterator(&items[0]); }
//        SetIterator<reference> end() { return Iterator(&items[100]); }
//        void print() const {
//            std::ranges::for_each(stl_set, [](const auto &el) { std::cout << el << ' '; });
//            std::cout << '\n';
//        }
    private:
        value_type items[100];
    };

}

#include "set.hpp"

#endif //MADE22_C_SET_H
