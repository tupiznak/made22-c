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

        explicit Node(const_reference key) : _key(key) {};
        inline auto smallRotateRight() noexcept {
            auto *const p = this;
            auto *const q = left;
            p->left = q->right;
            q->right = p;
            p->updateHeight();
            q->updateHeight();
            return q;
        }
        inline auto smallRotateLeft() noexcept {
            auto *const p = this;
            auto *const q = right;
            p->right = q->left;
            q->left = p;
            p->updateHeight();
            q->updateHeight();
            return q;
        }
        inline auto bigRotateRight() noexcept {
            auto *const p = this;
            auto *const q = left;
            p->left = q->smallRotateLeft();
            return p->smallRotateRight();
        }
        inline auto bigRotateLeft() noexcept {
            auto *const p = this;
            auto *const q = right;
            p->right = q->smallRotateRight();
            return p->smallRotateLeft();
        }

        inline void updateHeight() noexcept {
            const auto height_left = getHeight(left);
            const auto height_right = getHeight(right);
            height = std::max(height_left, height_right) + 1;
        }

        auto balance() -> Node * {
            const auto curr_balance = getBalance();
            updateHeight();
            if (curr_balance > 1) {
                if (right != nullptr && right->getBalance() < 0) { return bigRotateLeft(); }
                return smallRotateLeft();
            } else if (curr_balance < -1) {
                if (left != nullptr && left->getBalance() > 0) { return bigRotateRight(); }
                return smallRotateRight();
            }
            return this;
        }

        [[nodiscard]] inline auto getKey() const noexcept -> const_reference { return _key; }
        [[nodiscard]] inline auto getRight() const noexcept -> Node * { return right; }
        [[nodiscard]] inline auto getLeft() const noexcept -> Node * { return left; }
        [[nodiscard]] static inline auto getHeight(const Node *const vertex) noexcept -> unsigned {
            return vertex != nullptr ? vertex->height : 0;
        }
        [[nodiscard]] inline auto getBalance() const noexcept -> int { return getHeight(right) - getHeight(left); }

        static auto insert(Node *curr_vertex, const_reference key) -> Node * {
            if (curr_vertex == nullptr) {
                curr_vertex = new Node(key);
                return curr_vertex;
            }
            if (key < curr_vertex->_key) {
                auto *const sub_tree = insert(curr_vertex->left, key);
                if (sub_tree == nullptr) { return nullptr; }
                curr_vertex->left = sub_tree;
            } else if (key > curr_vertex->_key) {
                auto *const sub_tree = insert(curr_vertex->right, key);
                if (sub_tree == nullptr) { return nullptr; }
                curr_vertex->right = sub_tree;
            } else { return nullptr; }
            return curr_vertex->balance();
        };
        static auto erase(Node *curr_vertex, const_reference key) -> Node * {
            if (curr_vertex == nullptr) { return nullptr; }
            if (key < curr_vertex->_key) {
                curr_vertex->left = erase(curr_vertex->left, key);
            } else if (key > curr_vertex->_key) {
                curr_vertex->right = erase(curr_vertex->right, key);
            } else if (curr_vertex->right == nullptr && curr_vertex->left == nullptr) {
                delete curr_vertex;
                curr_vertex = nullptr;
            } else if (curr_vertex->left == nullptr) {
                auto *right = curr_vertex->right;
                delete curr_vertex;
                curr_vertex = right;
            } else if (curr_vertex->right == nullptr) {
                auto *left = curr_vertex->left;
                delete curr_vertex;
                curr_vertex = left;
            } else {
                curr_vertex->_key = findMax(curr_vertex->left)->_key;
                curr_vertex->left = erase(curr_vertex->left, curr_vertex->_key);
            }
            if (curr_vertex == nullptr) { return nullptr; }
            return curr_vertex->balance();
        };

        static auto contains(Node *curr_vertex, const_reference key) -> Node * {
            if (curr_vertex == nullptr) { return curr_vertex; }
            if (key < curr_vertex->_key) { return contains(curr_vertex->left, key); }
            else if (key > curr_vertex->_key) { return contains(curr_vertex->right, key); }
            return curr_vertex;
        }

        inline static auto findMax(Node *curr_vertex) noexcept -> Node * {
            if (curr_vertex == nullptr) { return nullptr; }
            while (curr_vertex->right != nullptr) { curr_vertex = curr_vertex->right; }
            return curr_vertex;
        }

        static void printTree(Node *curr_vertex) noexcept {
            if (curr_vertex == nullptr) { return; }
            printTree(curr_vertex->left);
            std::cout << curr_vertex->_key << " ";
            printTree(curr_vertex->right);
        }


    private:
        value_type _key;
        unsigned height{1};
        Node *left{};
        Node *right{};
    };

}

#endif //CONTAINER_NODE_H
