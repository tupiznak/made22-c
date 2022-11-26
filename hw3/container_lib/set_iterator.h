#ifndef CONTAINER_SET_ITERATOR_H
#define CONTAINER_SET_ITERATOR_H

#include <iterator>

namespace hw3 {
    template<class I>
    struct SetIterator {
        using iterator_category [[maybe_unused]] = std::bidirectional_iterator_tag;
        using difference_type [[maybe_unused]] = std::ptrdiff_t;
        using value_type = I;

        SetIterator() = default;
        explicit SetIterator(const value_type *ptr) : _ptr{ptr} {}

        auto &operator=(const auto &other);
        auto operator*() const { return *_ptr; }
        auto operator->() { return _ptr; }
        auto &operator++();
        auto operator++(int);
        auto &operator--();
        auto operator--(int);
        friend bool operator==(const SetIterator &a, const SetIterator &b) { return a._ptr == b._ptr; };
        friend bool operator!=(const SetIterator &a, const SetIterator &b) { return a._ptr != b._ptr; };

        void swap(const auto &) {};
    private:
        const value_type *_ptr;
    };
}

#include "set_iterator.hpp"

#endif //CONTAINER_SET_ITERATOR_H
