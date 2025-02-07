#include "RBTree.h"

void CalculateSize(Node *node) {
    if (node == nullptr) {
        return;
    }

    node->size = 1;
    if (node->left != nullptr) {
        node->size += node->left->size;
    }
    if (node->right != nullptr) {
        node->size += node->right->size;
    }
}

void rotateLeft(RBTree *tree, Node *node) {
    Node *right = node->right;
    node->right = right->left;
    if (right->left != nullptr) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == nullptr) {
        tree->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;

    CalculateSize(node);
    CalculateSize(right);
}

void rotateRight(RBTree *tree, Node *node) {
    Node *left = node->left;
    node->left = left->right;
    if (left->right != nullptr) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == nullptr) {
        tree->root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;

    CalculateSize(node);
    CalculateSize(left);
}

Node::Node(int key) {
    this->key = key;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = Color::RED;
    size = 1;
}

RBTree::RBTree() {
    root = nullptr;
}

RBTree::RBTree(std::initializer_list<int> list) {
    root = nullptr;
    for (int key : list) {
        insert(key);
    }
}

RBTree::RBTree(const std::vector<int>& list) {
    root = nullptr;
    for (int key : list) {
        insert(key);
    }
}

RBTree::~RBTree() {
    delete root;
}

void RBTree::insert(int key) {
    if (find(key).first != nullptr) {
        return;
    }

    Node *node = new Node(key);
    Node *parent = nullptr;
    Node *current = root;
    while (current != nullptr) {
        parent = current;
        ++parent->size;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;
    if (parent == nullptr) {
        root = node;
        node->color = Color::BLACK;
        return;
    } else if (key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }


    while (node != root && node->parent->color == Color::RED) {
        parent = node->parent;
        Node *grandparent = parent->parent;
        if (grandparent == nullptr) {
            break;
        }

        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(this, node);
                    parent = node->parent;
                }
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(this, grandparent);
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotateRight(this, node);
                    parent = node->parent;
                }
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(this, grandparent);
            }
        }
    }

    root->color = Color::BLACK;
}

std::pair<int*, int> RBTree::find(int key) {
    Node *current = root;
    int operations = 0;
    while (current != nullptr) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return {&current->key, operations};
        }
        ++operations;
    }

    return {nullptr, operations};
}

int RBTree::size() const {
    return root == nullptr ? 0 : root->size;
}

int *RBTree::lowerBound(int key) {
    Node *current = root;
    Node *result = nullptr;
    while (current != nullptr) {
        if (key < current->key) {
            result = current;
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return &current->key;
        }
    }

    return result == nullptr ? nullptr : &result->key;
}

bool RBTree::empty() const {
    return root == nullptr;
}

