// этот файл сдавал на алгоритмах => пройдены тесты в тестирующей системе. начинку дерева брал из него.
// могу удалить, если мешает.

#include <gtest/gtest.h>
#include <algorithm>
#include <string_view>
#include <ranges>
#include <iostream>
#include <cstring>
#include <numeric>

class Node final {
public:
    explicit Node(const int &key, Node *parent) : _key(key), parent{parent} {};
    inline auto smallRotateRight() noexcept {
        auto *const p = this;
        auto *const q = left;
        p->left = q->right;
        q->right = p;

        if (p->left != nullptr) { p->left->parent = p; }
        q->parent = p->parent;
        p->parent = q;

        p->updateHeight();
        q->updateHeight();
        return q;
    }
    inline auto smallRotateLeft() noexcept {
        auto *const p = this;
        auto *const q = right;
        p->right = q->left;
        q->left = p;

        if (p->right != nullptr) { p->right->parent = p; }
        q->parent = p->parent;
        p->parent = q;

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
        const auto size_left = getSize(left);
        const auto size_right = getSize(right);
        size = size_left + size_right + 1;
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

    [[nodiscard]] inline auto getKey() const noexcept -> int { return _key; }
    [[nodiscard]] inline auto getRight() const noexcept -> Node * { return right; }
    [[nodiscard]] inline auto getLeft() const noexcept -> Node * { return left; }
    [[nodiscard]] static inline auto getHeight(const Node *const vertex) noexcept -> int {
        return vertex != nullptr ? vertex->height : 0;
    }
    [[nodiscard]] static inline auto getSize(const Node *const vertex) noexcept -> int {
        return vertex != nullptr ? vertex->size : 0;
    }
    [[nodiscard]] inline auto getBalance() const noexcept -> int { return getHeight(right) - getHeight(left); }

    static auto insert(Node *curr_vertex, Node *parent_vertex, const int &key) -> Node * {
        if (curr_vertex == nullptr) {
            curr_vertex = new Node(key, parent_vertex);
            return curr_vertex;
        }
        if (key < curr_vertex->_key) {
            curr_vertex->left = insert(curr_vertex->left, curr_vertex, key);
        } else if (key > curr_vertex->_key) {
            curr_vertex->right = insert(curr_vertex->right, curr_vertex, key);
        }
        return curr_vertex->balance();
    };
    static auto erase(Node *curr_vertex, const int &key) -> Node * {
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

    static auto contains(Node *curr_vertex, const int &key) -> Node * {
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
    inline static auto findMin(Node *curr_vertex) noexcept -> Node * {
        if (curr_vertex == nullptr) { return nullptr; }
        while (curr_vertex->left != nullptr) { curr_vertex = curr_vertex->left; }
        return curr_vertex;
    }
    [[nodiscard]] auto findK(const int &k) const noexcept -> const Node * {
        if (getSize(left) + 1 == k) { return this; }
        if (k > getSize(left) + 1) { return right->findK(k - getSize(left) - 1); }
        return left->findK(k);
    }

    static void printTree(Node *curr_vertex) noexcept {
        if (curr_vertex == nullptr) { return; }
        printTree(curr_vertex->left);
        std::cout << curr_vertex->_key << " ";
        printTree(curr_vertex->right);
    }

    const Node *prev() noexcept {
        if (left != nullptr) { return findMax(left); }
        if (parent == nullptr || parent->right == this) { return parent; }
        const auto *curr_vertex = this;
        while (curr_vertex->parent != nullptr && curr_vertex->parent->left == curr_vertex) {
            curr_vertex = curr_vertex->parent;
        }
        if (curr_vertex->parent == nullptr) { return nullptr; }
        return curr_vertex->parent;
    }

    const Node *next() noexcept {
        if (right != nullptr) { return findMin(right); }
        if (parent == nullptr || parent->left == this) { return parent; }
        const auto *curr_vertex = this;
        while (curr_vertex->parent != nullptr && curr_vertex->parent->right == curr_vertex) {
            curr_vertex = curr_vertex->parent;
        }
        if (curr_vertex->parent == nullptr) { return nullptr; }
        return curr_vertex->parent;
    }


private:
    int _key;
    int height{1};
    Node *left{};
    Node *right{};
    Node *parent;
    int size{1};
};

class AVL final {
public:
    AVL() = default;
    AVL(std::initializer_list<int> init) { std::ranges::for_each(init, [this](const int &el) { insert(el); }); };
    void insert(const int &key) {
        ++elements_count;
        root = Node::insert(root, nullptr, key);
    };
    void erase(const int &key) {
        --elements_count;
        root = Node::erase(root, key);
    };
    auto contains(const int &key) -> bool { return Node::contains(root, key) != nullptr; };
    void printTree() { Node::printTree(root); }
    auto next(const int &key) const -> const Node * {
        auto *curr = Node::contains(root, key);
        if (curr == nullptr) { return nullptr; }
        return curr->next();

//        auto *curr_vertex = root;
//        Node *target = nullptr;
//        while (curr_vertex != nullptr) {
//            if (curr_vertex->getKey() > key) {
//                target = curr_vertex;
//                curr_vertex = curr_vertex->getLeft();
//            } else {
//                curr_vertex = curr_vertex->getRight();
//            }
//        }
//        return target;
    };
    auto prev(const int &key) -> const Node * {
        auto *curr = Node::contains(root, key);
        if (curr == nullptr) { return nullptr; }
        return curr->prev();

        auto *curr_vertex = root;
        Node *target = nullptr;
        while (curr_vertex != nullptr) {
            if (curr_vertex->getKey() < key) {
                target = curr_vertex;
                curr_vertex = curr_vertex->getRight();
            } else {
                curr_vertex = curr_vertex->getLeft();
            }
        }
        return target;
    };
    int findKMax(const int &k) { return root->findK(elements_count - k + 1)->getKey(); }

private:
    Node *root{};
    int elements_count{0};
};

auto main1() -> int {
    auto avl = AVL{};
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.starts_with("insert ")) {
            avl.insert(std::stoi(line.substr(strlen("insert "))));
        } else if (line.starts_with("delete ")) {
            avl.erase(std::stoi(line.substr(strlen("delete "))));
        } else if (line.starts_with("exists ")) {
            const auto res = avl.contains(std::stoi(line.substr(strlen("exists "))));
            std::cout << (res ? "true" : "false") << "\n";
        } else if (line.starts_with("next ")) {
            const auto res = avl.next(std::stoi(line.substr(strlen("next "))));
            std::cout << (res != nullptr ? std::to_string(res->getKey()) : "none") << "\n";
        } else if (line.starts_with("prev ")) {
            const auto res = avl.prev(std::stoi(line.substr(strlen("prev "))));
            std::cout << (res != nullptr ? std::to_string(res->getKey()) : "none") << "\n";
        } else {
            throw std::runtime_error("");
        }
    }
};

TEST(BasicAvl, Check) {
    {
        std::vector<int> x(7);
        std::iota(std::begin(x), std::end(x), 0);
        auto avl = AVL{};
        std::ranges::for_each(x, [&](const int &el) { avl.insert(el); });
        avl.printTree();
        std::cout << "\n" << avl.findKMax(7) << "\n";
    }
    {
        auto avl = AVL{2, 3, 4, 5, 1, 0};
        avl.insert(4);
        avl.printTree();
        EXPECT_EQ(true, avl.contains(3));
        EXPECT_EQ(false, avl.contains(30));
        EXPECT_EQ(nullptr, avl.next(30));
        EXPECT_EQ(4, avl.next(3)->getKey());
        EXPECT_EQ(2, avl.next(1)->getKey());
        EXPECT_EQ(3, avl.next(2)->getKey());
        EXPECT_EQ(nullptr, avl.next(5));
        EXPECT_EQ(5, avl.next(4)->getKey());
        EXPECT_EQ(1, avl.next(0)->getKey());

        EXPECT_EQ(2, avl.prev(3)->getKey());
        EXPECT_EQ(nullptr, avl.prev(0));
        EXPECT_EQ(0, avl.prev(1)->getKey());
        EXPECT_EQ(1, avl.prev(2)->getKey());
        EXPECT_EQ(4, avl.prev(5)->getKey());
        EXPECT_EQ(3, avl.prev(4)->getKey());
        EXPECT_EQ(2, avl.prev(3)->getKey());
    }
    {
        auto avl = AVL{2, 3, 4, 5, 1, 0};
        avl.insert(3);
    }
}
