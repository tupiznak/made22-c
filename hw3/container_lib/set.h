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
            auto *const tree = _insert(root, nullptr, key);
            if (tree == nullptr) { return; }
            root = tree;
            ++elements_count;
        };
        void erase(const_reference key) {
            if (!contains(key)) { return; }
            root = _erase(root, nullptr, key);
            --elements_count;
        };
        bool contains(const_reference key) { return _contains(root, key) != nullptr; };
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
            const auto *vertex = _contains(root, key);
            return vertex != nullptr ? SetIterator<value_type>(vertex) : end();
        }

    private:
        inline Node<value_type> *_smallRotateRight(Node<value_type> *joint_vertex) const noexcept {
            auto *const p = joint_vertex;
            auto *const q = joint_vertex->left;
            p->left = q->right;
            q->right = p;

            if (p->left != nullptr) { p->left->parent = p; }
            q->parent = p->parent;
            p->parent = q;

            p->updateHeight();
            q->updateHeight();
            return q;
        }
        inline Node<value_type> *_smallRotateLeft(Node<value_type> *joint_vertex) const noexcept {
            auto *const p = joint_vertex;
            auto *const q = joint_vertex->right;
            p->right = q->left;
            q->left = p;

            if (p->right != nullptr) { p->right->parent = p; }
            q->parent = p->parent;
            p->parent = q;

            p->updateHeight();
            q->updateHeight();
            return q;
        }
        inline Node<value_type> *_bigRotateRight(Node<value_type> *joint_vertex) const noexcept {
            auto *const p = joint_vertex;
            auto *const q = joint_vertex->left;
            p->left = _smallRotateLeft(q);
            return _smallRotateRight(p);
        }
        inline Node<value_type> *_bigRotateLeft(Node<value_type> *joint_vertex) const noexcept {
            auto *const p = joint_vertex;
            auto *const q = joint_vertex->right;
            p->right = _smallRotateRight(q);
            return _smallRotateLeft(p);
        }

        Node<value_type> *_balance(Node<value_type> *joint_vertex) const {
            const auto curr_balance = joint_vertex->getBalance();
            joint_vertex->updateHeight();
            if (curr_balance > 1) {
                if (joint_vertex->right != nullptr && joint_vertex->right->getBalance() < 0) {
                    return _bigRotateLeft(joint_vertex);
                }
                return _smallRotateLeft(joint_vertex);
            } else if (curr_balance < -1) {
                if (joint_vertex->left != nullptr && joint_vertex->left->getBalance() > 0) {
                    return _bigRotateRight(joint_vertex);
                }
                return _smallRotateRight(joint_vertex);
            }
            return joint_vertex;
        }

        Node<value_type> *
        _insert(Node<value_type> *curr_vertex, Node<value_type> *parent_vertex, const_reference key) const {
            if (curr_vertex == nullptr) {
                curr_vertex = new Node<value_type>(key, parent_vertex);
                return curr_vertex;
            }
            if (key < curr_vertex->_key) {
                auto *const sub_tree = _insert(curr_vertex->left, curr_vertex, key);
                if (sub_tree == nullptr) { return nullptr; }
                curr_vertex->left = sub_tree;
            } else if (curr_vertex->_key < key) {
                auto *const sub_tree = _insert(curr_vertex->right, curr_vertex, key);
                if (sub_tree == nullptr) { return nullptr; }
                curr_vertex->right = sub_tree;
            } else { return nullptr; }
            return _balance(curr_vertex);
        };
        Node<value_type> *
        _erase(Node<value_type> *curr_vertex, Node<value_type> *parent_vertex, const_reference key) const {
            if (curr_vertex == nullptr) { return nullptr; }
            if (key < curr_vertex->_key) {
                curr_vertex->left = _erase(curr_vertex->left, curr_vertex, key);
            } else if (curr_vertex->_key < key) {
                curr_vertex->right = _erase(curr_vertex->right, curr_vertex, key);
            } else if (curr_vertex->right == nullptr && curr_vertex->left == nullptr) {
                if (parent_vertex) {
                    parent_vertex->left == curr_vertex ? parent_vertex->left = nullptr : parent_vertex->right = nullptr;
                }
                delete curr_vertex;
                curr_vertex = nullptr;
            } else if (curr_vertex->left == nullptr) {
                auto *right = curr_vertex->right;
                if (parent_vertex) {
                    parent_vertex->left == curr_vertex ? parent_vertex->left = right : parent_vertex->right = right;
                }
                right->parent = parent_vertex;
                curr_vertex->right = nullptr;
                delete curr_vertex;
                curr_vertex = right;
            } else if (curr_vertex->right == nullptr) {
                auto *left = curr_vertex->left;
                if (parent_vertex) {
                    parent_vertex->left == curr_vertex ? parent_vertex->left = left : parent_vertex->right = left;
                }
                left->parent = parent_vertex;
                curr_vertex->left = nullptr;
                delete curr_vertex;
                curr_vertex = left;
            } else {
                curr_vertex->_key = Node<value_type>::findMax(curr_vertex->left)->_key;
                curr_vertex->left = _erase(curr_vertex->left, curr_vertex, curr_vertex->_key);
            }
            if (curr_vertex == nullptr) { return nullptr; }
            return _balance(curr_vertex);
        };

        Node<value_type> *_contains(Node<value_type> *curr_vertex, const_reference key) const {
            if (curr_vertex == nullptr) { return curr_vertex; }
            if (key < curr_vertex->_key) { return _contains(curr_vertex->left, key); }
            else if (curr_vertex->_key < key) { return _contains(curr_vertex->right, key); }
            return curr_vertex;
        }

        Node<value_type> *root{};
        unsigned elements_count{0};
    };

}

#endif //MADE22_C_SET_H
