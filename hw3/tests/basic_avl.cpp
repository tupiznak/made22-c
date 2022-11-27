#include <gtest/gtest.h>
#include <algorithm>
#include <string_view>
#include <ranges>
#include <iostream>
#include <cstring>
#include <numeric>

class Node final {
public:
    explicit Node(const int &key) : _key(key) {};
    auto smallRotateRight() noexcept {
        const auto p = this;
        const auto q = left;
        p->left = q->right;
        q->right = p;
        p->updateHeight();
        q->updateHeight();
        return q;
    }
    auto smallRotateLeft() noexcept {
        const auto p = this;
        const auto q = right;
        right = left;
        p->right = q->left;
        q->left = p;
        p->updateHeight();
        q->updateHeight();
        return q;
    }
    auto bigRotateRight() noexcept {
        const auto p = this;
        const auto q = left;
        p->left = q->smallRotateLeft();
        return p->smallRotateRight();
    }
    auto bigRotateLeft() noexcept {
        const auto p = this;
        const auto q = right;
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
            if (right != nullptr && right->getBalance() < 0) {
                return bigRotateLeft();
            } else {
                return smallRotateLeft();
            }
        } else if (curr_balance < -1) {
            if (left != nullptr && left->getBalance() > 0) {
                return bigRotateRight();
            } else { return smallRotateRight(); }
        }
        return this;
    }
//    static inline void updateHeight(Node *const vertex) noexcept {
//        if (vertex == nullptr) { return; }
//        const auto height_left = getHeight(vertex->left);
//        const auto height_right = getHeight(vertex->right);
//        vertex->height = std::max(height_left, height_right) + 1;
//    }

    [[nodiscard]] inline auto getKey() const noexcept -> int { return _key; }
    [[nodiscard]] inline auto getRight() const noexcept -> Node * { return right; }
    [[nodiscard]] inline auto getLeft() const noexcept -> Node * { return left; }
    [[nodiscard]] static inline auto getHeight(const Node *const vertex) noexcept -> int {
        return vertex != nullptr ? vertex->height : 0;
    }
    [[nodiscard]] inline int getBalance() const noexcept {
        return getHeight(right) - getHeight(left);
    }

    static auto insert(Node *curr_vertex, const int &key) -> Node * {
        if (curr_vertex == nullptr) {
            curr_vertex = new Node(key);
            return curr_vertex;
        }
        if (key < curr_vertex->_key) {
            curr_vertex->left = insert(curr_vertex->left, key);
        } else if (key > curr_vertex->_key) {
            curr_vertex->right = insert(curr_vertex->right, key);
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
        if (curr_vertex == nullptr) {
            return curr_vertex;
        } else if (key < curr_vertex->_key) {
            return contains(curr_vertex->left, key);
        } else if (key > curr_vertex->_key) {
            return contains(curr_vertex->right, key);
        }
        return curr_vertex;
    }

    inline static auto findMax(Node *curr_vertex) noexcept -> Node * {
        if (curr_vertex == nullptr) {
            return nullptr;
        }
        while (curr_vertex->right != nullptr) {
            curr_vertex = curr_vertex->right;
        }
        return curr_vertex;
    }

    static void printTree(Node *curr_vertex) noexcept {
        if (curr_vertex == nullptr) { return; }
        printTree(curr_vertex->left);
        std::cout << curr_vertex->_key << " ";
        printTree(curr_vertex->right);
    }


private:
    int _key;
    int height{1};
    Node *left{};
    Node *right{};
};

class AVL final {
public:
    AVL() = default;
    AVL(std::initializer_list<int> init) { std::ranges::for_each(init, [this](const int &el) { insert(el); }); };
    void insert(const int &key) { root = Node::insert(root, key); };
    void erase(const int &key) { root = Node::erase(root, key); };
    bool contains(const int &key) { return Node::contains(root, key) != nullptr; };
    void printTree() { Node::printTree(root); }
    auto next(const int &key) const -> Node * {
        auto curr_vertex = root;
        Node *target = nullptr;
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
    auto prev(const int &key) const -> Node * {
        auto curr_vertex = root;
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

private:
    Node *root{};
};

int main1() {
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
        } else throw std::runtime_error("");
    }
};

TEST(BasicAvl, Check) {
    {
        std::vector<int> x(70);
        std::iota(std::begin(x), std::end(x), 0);
        auto avl = AVL{};
        std::ranges::for_each(x, [&](const int &el) { avl.insert(el); });
        avl.printTree();
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
