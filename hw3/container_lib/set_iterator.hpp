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
    if (_ptr->getRight() != nullptr) {
        _ptr = Node<I>::findMin(_ptr->getRight());
        return *this;
    }
    if (_ptr->getParent() == nullptr || _ptr->getParent()->getLeft() == _ptr) {
        _ptr = _ptr->getParent();
        return *this;
    }
    const auto *curr_vertex = _ptr;
    while (curr_vertex->getParent() != nullptr && curr_vertex->getParent()->getRight() == curr_vertex) {
        curr_vertex = curr_vertex->getParent();
    }
    _ptr = curr_vertex->getParent();
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
