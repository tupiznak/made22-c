#pragma once

#include "set.h"

template<class T>
hw3::Set<T>::Set(std::initializer_list<T> init) {
    std::ranges::for_each(init, [&](const_reference el) { insert(el); });
}

