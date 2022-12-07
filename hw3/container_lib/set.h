#ifndef MADE22_C_SET_H
#define MADE22_C_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <ranges>

#include "set_iterator.h"
#include "node.h"

namespace hw3 {
    template<class T>
    class Set {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = std::initializer_list<T>;
        using const_iterator = std::initializer_list<T>;
        using size_type = size_t;
        using pointer = T *;
        using const_pointer = const T *;

        Set() = default;
        Set(std::initializer_list<value_type> init);

        void insert(const_reference key) {
            auto *const tree = Node<value_type>::insert(root, nullptr, key);
            if (tree == nullptr) { return; }
            root = tree;
            ++elements_count;
        };
        void erase(const_reference key) {
            root = Node<value_type>::erase(root, nullptr, key);
            --elements_count;
        };
        auto contains(const_reference key) -> bool { return Node<value_type>::contains(root, key) != nullptr; };
        void printTree() { Node<value_type>::printTree(root); }
        auto lower_bound(const_reference key) const -> Node<value_type> * {
            auto *curr_vertex = root;
            Node<value_type> *target = nullptr;
            while (curr_vertex != nullptr) {
                if (curr_vertex->getKey() >= key) {
                    target = curr_vertex;
                    curr_vertex = curr_vertex->getLeft();
                } else {
                    curr_vertex = curr_vertex->getRight();
                }
            }
            return target;
        };
        auto upper_bound(const_reference key) const -> Node<value_type> * {
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
            return target;
        };

        auto begin() { return Node<value_type>::findMin(root); }
        auto end() { return Node<value_type>::findMax(root); }
    private:
        Node<value_type> *root{};
        unsigned elements_count{0};
    };

}

#include "set.hpp"

#endif //MADE22_C_SET_H
