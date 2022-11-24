#ifndef CONTAINER_SET_ITERATOR_H
#define CONTAINER_SET_ITERATOR_H

#include <iterator>

namespace hw3 {
    template<class I>
    struct SetIterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = I;

        SetIterator();
        SetIterator(auto ptr) : _ptr(ptr) {}

        auto &operator=(const auto &);
        auto operator*() const { return *_ptr; }
        auto operator->() { return _ptr; }
        SetIterator &operator++() {
            _ptr++;
            return *this;
        }
        SetIterator operator++(int) {
            SetIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        friend bool operator==(const SetIterator &a, const SetIterator &b) { return a._ptr == b._ptr; };
        friend bool operator!=(const SetIterator &a, const SetIterator &b) { return a._ptr != b._ptr; };
//        friend auto operator<=>(SetIterator, SetIterator) = default;

        SetIterator &operator--();
        SetIterator operator--(int);
    private:
        I *_ptr;
    };

}

#include "set_iterator.hpp"

#endif //CONTAINER_SET_ITERATOR_H
