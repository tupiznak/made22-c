#ifndef CONTAINER_NODE_H
#define CONTAINER_NODE_H

#include <algorithm>
#include <string_view>
#include <ranges>
#include <iostream>
#include <cstring>
#include <numeric>

namespace hw3 {

    template<class T>
    class Node final {
    public:
        using value_type = T;
        using const_reference = const T &;

        explicit Node(const_reference key, Node *parent) : _key(key), parent{parent} {};
        ~Node() {
            if (left != nullptr) { delete left; }
            if (right != nullptr) { delete right; }
        }

        inline void updateHeight() noexcept {
            const auto height_left = getHeight(left);
            const auto height_right = getHeight(right);
            height = std::max(height_left, height_right) + 1;
        }
        static inline unsigned getHeight(const Node *const vertex) noexcept {
            return vertex != nullptr ? vertex->height : 0;
        }
        inline int getBalance() const noexcept { return getHeight(right) - getHeight(left); }

        inline static Node *findMax(Node<value_type> *curr_vertex) noexcept {
            if (curr_vertex == nullptr) { return nullptr; }
            while (curr_vertex->right != nullptr) { curr_vertex = curr_vertex->right; }
            return curr_vertex;
        }

        inline static Node *findMin(Node *curr_vertex) noexcept {
            if (curr_vertex == nullptr) { return nullptr; }
            while (curr_vertex->left != nullptr) { curr_vertex = curr_vertex->left; }
            return curr_vertex;
        }
        Node *prev() noexcept {
            if (left != nullptr) { return findMax(left); }
            if (parent == nullptr || parent->right == this) { return parent; }
            const auto *curr_vertex = this;
            while (curr_vertex->parent != nullptr && curr_vertex->parent->left == curr_vertex) {
                curr_vertex = curr_vertex->parent;
            }
            return curr_vertex->parent;
        }

        Node *next() noexcept {
            if (right != nullptr) { return findMin(right); }
            if (parent == nullptr || parent->left == this) { return parent; }
            const auto *curr_vertex = this;
            while (curr_vertex->parent != nullptr && curr_vertex->parent->right == curr_vertex) {
                curr_vertex = curr_vertex->parent;
            }
            return curr_vertex->parent;
        }


    private:
        template<class U>
        friend
        class Set;

        template<class U>
        friend
        class SetIterator;

        inline const_reference getKey() const noexcept { return _key; }
        inline Node *getRight() const noexcept { return right; }
        inline Node *getLeft() const noexcept { return left; }
        inline Node *getParent() const noexcept { return parent; }

        value_type _key;
        unsigned height{1};
        Node *left{};
        Node *right{};
        Node *parent;
    };

}

#endif //CONTAINER_NODE_H
