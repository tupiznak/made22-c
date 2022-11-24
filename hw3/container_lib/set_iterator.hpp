#pragma once

#include "set_iterator.h"

template<class I>
auto &hw3::SetIterator<I>::operator=(const auto &other) {
    if (this != &other) {
        SetIterator(other).swap(*this);
    }
    return *this;
}

template<class I>
auto &hw3::SetIterator<I>::operator++() {
    ++_ptr;
    return *this;
}

template<class I>
auto hw3::SetIterator<I>::operator++(int) {
    ++_ptr;
    return *this;
}

template<class I>
auto &hw3::SetIterator<I>::operator--() {
    --_ptr;
    return *this;
}

template<class I>
auto hw3::SetIterator<I>::operator--(int) {
    --_ptr;
    return *this;
}
