#pragma once

#include <initializer_list>
#include <vector>
#include <utility>

enum class Color { RED, BLACK };
 
struct Node {
    int key;
    int height;
    int size;
    Node *left;
    Node *right;
    Node *parent;
    Color color;
 
    explicit Node(int key);
};
 
class RBTree {
public:
    RBTree();
 
    RBTree(std::initializer_list<int> list);
    explicit RBTree(const std::vector<int>& list);

    ~RBTree();
 
    void insert(int key);
    
    std::pair<int*, int> find(int key);
    
    [[nodiscard]] int size() const;
 
    int *lowerBound(int key);
 
    [[nodiscard]] bool empty() const;

    Node *root = nullptr;
 
};