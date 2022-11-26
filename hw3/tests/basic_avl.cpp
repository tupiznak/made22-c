#include <gtest/gtest.h>
#include <algorithm>

class Node final {
public:
    explicit Node(const int &key) : _key(key) {};
    static Node *insert(Node *curr_vertex, const int &key) {
        if (curr_vertex == nullptr) {
            curr_vertex = new Node(key);
            return curr_vertex;
        }
        if (key < curr_vertex->_key) {
            curr_vertex->left = insert(curr_vertex->left, key);
        } else if (key > curr_vertex->_key) {
            curr_vertex->right = insert(curr_vertex->right, key);
        }
        return curr_vertex;
    };
    static Node *erase(Node *curr_vertex, const int &key) {
        if (curr_vertex == nullptr) {
            return nullptr;
        }
        if (key < curr_vertex->_key) {
            curr_vertex->left = erase(curr_vertex->left, key);
        } else if (key > curr_vertex->_key) {
            curr_vertex->right = erase(curr_vertex->right, key);
        } else if (curr_vertex->right == nullptr && curr_vertex->left == nullptr) {
            delete curr_vertex;
            curr_vertex = nullptr;
        } else if (curr_vertex->left == nullptr) {
            auto right = curr_vertex->right;
            delete curr_vertex;
            curr_vertex = right;
        } else if (curr_vertex->right == nullptr) {
            auto left = curr_vertex->left;
            delete curr_vertex;
            curr_vertex = left;
        } else {
            curr_vertex->_key = findMax(curr_vertex->left)->_key;
            curr_vertex->left = erase(curr_vertex->left, curr_vertex->_key);
        }
        return curr_vertex;
    };

    inline static Node *findMax(Node *curr_vertex) {
        while (curr_vertex->right != nullptr) {
            curr_vertex = curr_vertex->right;
        }
        return curr_vertex;
    }
    static void printTree(Node *curr_vertex) {
        if (curr_vertex == nullptr) {
            return;
        }
        printTree(curr_vertex->left);
        std::cout << curr_vertex->_key << " ";
        printTree(curr_vertex->right);
    }

private:
    int _key;
    Node *left{};
    Node *right{};
};

class AVL final {
public:
    AVL() = default;
    AVL(std::initializer_list<int> init) { std::ranges::for_each(init, [this](const int &el) { insert(el); }); };
    void insert(const int &key) { root = Node::insert(root, key); };
    void erase(const int &key) { root = Node::erase(root, key); };
    void printTree() { Node::printTree(root); }

private:
    Node *root{};
};

TEST(BasicAvl, Check) {
    auto avl = AVL{2, 3, 4, 5, 1, 0};
    avl.insert(4);
    avl.printTree();
}
