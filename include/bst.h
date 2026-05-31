// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
            return;
        }

        if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        } else {
            node->count++;
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    int search(Node* node, const T& key) const {
        if (node == nullptr) return 0;

        if (key < node->key) {
            return search(node->left, key);
        } else if (key > node->key) {
            return search(node->right, key);
        } else {
            return node->count;
        }
    }

    void collectNodes(Node* node, std::vector<Node*>& nodes) {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back(node);
        collectNodes(node->right, nodes);
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& key) {
        insert(root, key);
    }

    int depth() const {
        return depth(root);
    }

    int search(const T& key) const {
        return search(root, key);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printByFrequency(std::ostream& os) {
        if (root == nullptr) return;

        std::vector<Node*> nodes;
        collectNodes(root, nodes);

        std::sort(nodes.begin(), nodes.end(),
            [](Node* a, Node* b) {
                if (a->count != b->count) {
                    return a->count > b->count;
                }
                return a->key < b->key;
            });

        for (Node* node : nodes) {
            os << node->key << ": " << node->count << std::endl;
        }
    }
};
#endif  // INCLUDE_BST_H_
