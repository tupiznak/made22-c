#pragma once

#include "set.h"

template<class T>
hw3::Set<T>::Set(std::initializer_list<T> init) {
    std::ranges::for_each(init, [this](const T &el) { insert(el); });
}

template<class T>
void hw3::Set<T>::insert(const T &el) {
    std::cout << el << '\n';
}
