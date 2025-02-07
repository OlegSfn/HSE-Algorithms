#pragma once
#include <vector>

class SkipList {
public:
    explicit SkipList(const std::vector<int>& keys);
    ~SkipList();
    std::pair<bool,int> contains(int key);
    void print();

 private:
  struct Node {
    int key;
    Node* rightNeighbour;
    Node* downNeighbour;

    Node() : key(0), rightNeighbour(nullptr), downNeighbour(nullptr) {}
    explicit Node(int key) : key(key), rightNeighbour(nullptr), downNeighbour(nullptr) {}

    ~Node() {
        delete rightNeighbour;
    }
  };

  Node* head;
  int levels;
};

