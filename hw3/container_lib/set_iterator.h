#ifndef CONTAINER_SET_ITERATOR_H
#define CONTAINER_SET_ITERATOR_H

#include <iterator>
#include "node.h"

namespace hw3 {
    template<class I>
    struct SetIterator {
        using iterator_category [[maybe_unused]] = std::bidirectional_iterator_tag;
        using difference_type [[maybe_unused]] = std::ptrdiff_t;
        using value_type = I;

        SetIterator() = default;
        explicit SetIterator(const Node<value_type> *ptr) : _ptr{ptr}, is_last{ptr == nullptr} {}

        auto operator*() const { return _ptr->getKey(); }
        auto operator->() { return _ptr; }
        auto &operator++();
        auto operator++(int);
        auto &operator--();
        auto operator--(int);
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

#include "set_iterator.hpp"

#endif //CONTAINER_SET_ITERATOR_H
