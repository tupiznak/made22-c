#pragma once

#include "set_iterator.h"


template<class I>
auto &hw3::SetIterator<I>::operator++() {
    if (is_last) { return *this; }
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
    if (curr_vertex->getParent() == nullptr) {
        is_last = true;
        return *this;
    }
    _ptr = curr_vertex->getParent();
    return *this;
}

template<class I>
auto hw3::SetIterator<I>::operator++(int) {
    if (is_last) { return *this; }
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
    if (curr_vertex->getParent() == nullptr) {
        is_last = true;
        return *this;
    }
    _ptr = curr_vertex->getParent();
    return *this;
}

template<class I>
auto &hw3::SetIterator<I>::operator--() {
    if (is_last) {
        is_last = false;
        return *this;
    }
    if (_ptr->getLeft() != nullptr) {
        _ptr = Node<I>::findMax(_ptr->getLeft());
        return *this;
    }
    if (_ptr->getParent() == nullptr || _ptr->getParent()->getRight() == _ptr) {
        _ptr = _ptr->getParent();
        return *this;
    }
    const auto *curr_vertex = _ptr;
    while (curr_vertex->getParent() != nullptr && curr_vertex->getParent()->getLeft() == curr_vertex) {
        curr_vertex = curr_vertex->getParent();
    }
    _ptr = curr_vertex->getParent();
    return *this;
}

template<class I>
auto hw3::SetIterator<I>::operator--(int) {
    if (is_last) {
        is_last = false;
        return *this;
    }
    if (_ptr->getLeft() != nullptr) {
        _ptr = Node<I>::findMax(_ptr->getLeft());
        return *this;
    }
    if (_ptr->getParent() == nullptr || _ptr->getParent()->getRight() == _ptr) {
        _ptr = _ptr->getParent();
        return *this;
    }
    const auto *curr_vertex = _ptr;
    while (curr_vertex->getParent() != nullptr && curr_vertex->getParent()->getLeft() == curr_vertex) {
        curr_vertex = curr_vertex->getParent();
    }
    _ptr = curr_vertex->getParent();
    return *this;
}
