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
    if (_ptr->right != nullptr) { _ptr = Node<I>::findMin(_ptr->right); return *this; }
    if (_ptr->parent == nullptr || _ptr->parent->left == _ptr) { _ptr = _ptr->parent;  return *this; }
    const auto *curr_vertex = _ptr;
    while (curr_vertex->parent != nullptr && curr_vertex->parent->right == curr_vertex) {
        curr_vertex = curr_vertex->parent;
    }
    _ptr = curr_vertex->parent;
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
