#pragma once
#include<vector>


class HashLPTable {
 public:
    HashLPTable(int size);
    ~HashLPTable();
    bool insert(int key);
    bool remove(int key);
    int search(int key);
    void print();
    int size();

 private:
    enum class State {
        EMPTY,
        DELETED,
        OCCUPIED
    };

    std::vector<int> table_;
    std::vector<State> states_;
    int size_;
    double max_load_factor_ = 0.66;
    int hash(int key);
    void rehash(int newSize);
    double loadFactor();
};