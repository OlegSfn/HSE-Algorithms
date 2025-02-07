#pragma once
#include<vector>
#include<unordered_set>

class HashCuckooTable {
  struct Node {
    int key;
    int hash1;
    int hash2;

    Node() {
        key = -1;
        hash1 = -1;
        hash2 = -1;
    }

    Node(int key, int hash1, int hash2) {
        this->key = key;
        this->hash1 = hash1;
        this->hash2 = hash2;
    }
  };

 public:
    HashCuckooTable(int size);
    ~HashCuckooTable();
    bool insert(int key);
    bool search(int key);
    void print();

 private:
    std::vector<Node> table_1_;
    std::vector<Node> table_2_;
    int size_;

    int hash1(int key);
    int hash2(int key);

    bool canInsertOccupied(Node& insertNode, bool isInsertingInFirstTable, std::unordered_set<int>& visitedFirst, std::unordered_set<int>& visitedSecond);
    bool insertOccupied(Node& insertNode, bool isInsertingInFirstTable);

    bool searchImpl(int key, int curIndex, bool isTable1, int elementsChecked);

    void rehash(int newSize);
};

