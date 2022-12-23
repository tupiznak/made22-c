#ifndef MADE22_C_SET_H
#define MADE22_C_SET_H

#include <functional>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <iterator>

#include "set_iterator.h"
#include "node.h"

namespace hw3 {
    template<class T>
    class Set {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = SetIterator<T>;
        using const_iterator = std::initializer_list<T>;
        using size_type = size_t;
        using pointer = T *;
        using const_pointer = const T *;

        Set() = default;
        Set(std::initializer_list<value_type> init) {
            std::ranges::for_each(init, [&](const_reference el) { insert(el); });
        }
        template<class BidirectionalIt>
        Set(BidirectionalIt begin, BidirectionalIt end) {
            std::ranges::for_each(begin, end, [&](const auto &el) { insert(el); });
        }
        Set(const Set<T> &other) : Set(other.begin(), other.end()) {}
        Set &operator=(const Set &other) {
            if (&other == this) { return *this; }
            delete root;
            root = nullptr;
            std::ranges::for_each(other, [&](const auto &el) { insert(el); });
            elements_count = other.elements_count;
            return *this;
        }
        ~Set() { delete root; }

        void insert(const_reference key) {
            auto *const tree = Node<value_type>::insert(root, nullptr, key);
            if (tree == nullptr) { return; }
            root = tree;
            ++elements_count;
        };
        void erase(const_reference key) {
            if (!contains(key)) { return; }
            root = Node<value_type>::erase(root, nullptr, key);
            --elements_count;
        };
        bool contains(const_reference key) { return Node<value_type>::contains(root, key) != nullptr; };
        void printTree() { Node<value_type>::printTree(root); }
        SetIterator<value_type> lower_bound(const_reference key) const {
            auto *curr_vertex = root;
            Node<value_type> *target = nullptr;
            while (curr_vertex != nullptr) {
                if (!(curr_vertex->getKey() < key)) {
                    target = curr_vertex;
                    curr_vertex = curr_vertex->getLeft();
                } else {
                    curr_vertex = curr_vertex->getRight();
                }
            }
            if (target == nullptr) { return end(); }
            return SetIterator<value_type>(target);
        };
        SetIterator<value_type> upper_bound(const_reference key) const {
            auto *curr_vertex = root;
            Node<value_type> *target = nullptr;
            while (curr_vertex != nullptr) {
                if (curr_vertex->getKey() > key) {
                    target = curr_vertex;
                    curr_vertex = curr_vertex->getLeft();
                } else {
                    curr_vertex = curr_vertex->getRight();
                }
            }
            if (target == nullptr) { return end(); }
            return SetIterator<value_type>(target);
        };

        unsigned size() const { return elements_count; }
        bool empty() const { return size() == 0; }

        SetIterator<value_type> begin() const { return SetIterator<value_type>(Node<value_type>::findMin(root)); }
        SetIterator<value_type> end() const {
            return ++SetIterator<value_type>(Node<value_type>::findMax(root));
        }
        SetIterator<value_type> find(const_reference key) const {
            const auto *vertex = Node<value_type>::contains(root, key);
            return vertex != nullptr ? SetIterator<value_type>(vertex) : end();
        }
    private:
        Node<value_type> *root{};
        unsigned elements_count{0};
    };

}

#endif //MADE22_C_SET_H
