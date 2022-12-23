#ifndef CONTAINER_SET_ITERATOR_H
#define CONTAINER_SET_ITERATOR_H

#include <iterator>
#include "node.h"

namespace hw3 {
    template<class I>
    struct SetIterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = I;

        SetIterator() = default;
        explicit SetIterator(const Node<value_type> *ptr) : _ptr{ptr}, is_last{ptr == nullptr} {}

        auto operator*() const { return _ptr->getKey(); }
        auto operator->() { return &(_ptr->getKey()); }
        SetIterator &operator++() {
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
        };
        SetIterator operator++(int) {
            if (is_last) { return *this; }
            if (_ptr->getRight() != nullptr) {
                _ptr = Node<I>::findMin(_ptr->getRight());
                return *this;
            }
            if (_ptr->getParent() == nullptr || _ptr->getParent()->getLeft() == _ptr) {
                _ptr = _ptr->getParent();
                return *this;
            }
            const SetIterator *curr_vertex = _ptr;
            while (curr_vertex->getParent() != nullptr && curr_vertex->getParent()->getRight() == curr_vertex) {
                curr_vertex = curr_vertex->getParent();
            }
            if (curr_vertex->getParent() == nullptr) {
                is_last = true;
                return *this;
            }
            _ptr = curr_vertex->getParent();
            return *this;
        };
        SetIterator &operator--() {
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
        };
        SetIterator operator--(int) {
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
        };
        friend bool operator==(const SetIterator &a, const SetIterator &b) {
            return a._ptr == b._ptr && a.is_last == b.is_last;
        };
        friend bool operator!=(const SetIterator &a, const SetIterator &b) {
            return a._ptr != b._ptr || a.is_last != b.is_last;
        };

    private:
        const Node<value_type> *_ptr;
        bool is_last{false};
    };
}

#endif //CONTAINER_SET_ITERATOR_H
