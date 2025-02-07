#include "HashLPTable.h"
#include<iostream>

HashLPTable::HashLPTable(int size) {
    this->size_ = 0;
    states_.resize(size, State::EMPTY);
    table_.resize(size, -1);
}

HashLPTable::~HashLPTable() {
    table_.clear();
}

bool HashLPTable::insert(int key) {
//    if (loadFactor() > max_load_factor_) {
//        rehash(table_.size() * 2);
//    }

    int index = hash(key);
    while (states_[index] != State::EMPTY && states_[index] != State::DELETED && table_[index] != key) {
        index = (index + 1) % table_.size();
    }

    if (states_[index] == State::EMPTY || states_[index] == State::DELETED) {
        table_[index] = key;
        ++size_;
        states_[index] = State::OCCUPIED;
        return true;
    }

    return false;
}

bool HashLPTable::remove(int key) {
    int index = search(key);
    if (states_[index] == State::EMPTY) {
        return false;
    }

    table_[index] = -1;
    states_[index] = State::DELETED;
    --size_;
    return true;
}

int HashLPTable::search(int key) {
    int index = hash(key);

    for(int c = 0; c < table_.size(); ++c) {
        if (table_[index] == key) {
            return index;
        } else if (states_[index] == State::EMPTY) {
            return -1;
        }

        index = (index + 1) % table_.size();
    }

    return -1;
}

int HashLPTable::hash(int key) {
    return key % table_.size();
}


void HashLPTable::rehash(int newSize) {
    std::vector<int> elements;
    for(int i = 0; i < table_.size(); ++i){
        if (states_[i] == State::OCCUPIED) {
            elements.push_back(table_[i]);
        }
    }

    table_ = std::vector<int>(newSize, -1);
    states_ = std::vector<State>(newSize, State::EMPTY);
    size_ = 0;
    for(auto el : elements) {
        insert(el);
    }
}

double HashLPTable::loadFactor() {
    return (double)size_ / table_.size();
}
void HashLPTable::print() {
    for (int i = 0; i < table_.size(); ++i) {
        std::cout << table_[i] << " ";
    }
    std::cout << std::endl;
}
int HashLPTable::size() {
    return size_;
}
