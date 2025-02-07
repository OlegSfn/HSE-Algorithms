#include "HashCuckooTable.h"
#include <iostream>

HashCuckooTable::HashCuckooTable(int size) {
    this->size_ = 0;
    table_1_.resize(size);
    table_2_.resize(size);
}

HashCuckooTable::~HashCuckooTable() {
    table_1_.clear();
    table_2_.clear();
}

bool HashCuckooTable::insert(int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);
    
    if (table_1_[index1].key == -1) {
        table_1_[index1].key = key;
        table_1_[index1].hash1 = index1;
        table_1_[index1].hash2 = index2;
        ++size_;
        return true;
    } else if (table_1_[index1].key == key) {
        return false;
    }
    
    Node insertNode(key, index1, index2);
    std::unordered_set<int> visitedFirst;
    std::unordered_set<int> visitedSecond;
    
    while (!canInsertOccupied(insertNode, true, visitedFirst, visitedSecond)) {
        visitedFirst.clear();
        visitedSecond.clear();
        rehash(2*table_1_.size());
    }

    if (insertOccupied(insertNode, true)) {
        ++size_;
        return true;
    }

    return false;
}

int HashCuckooTable::hash1(int key) {
    return key%table_1_.size();
}

int HashCuckooTable::hash2(int key) {
    return (key/table_1_.size())%table_2_.size();
}

bool HashCuckooTable::insertOccupied(Node& insertNode, bool isInsertingInFirstTable) {
    int index = isInsertingInFirstTable ? insertNode.hash1 : insertNode.hash2;
    if (isInsertingInFirstTable) {
        if (table_1_[index].key == -1) {
            table_1_[index] = insertNode;
            return true;
        } else if (table_1_[index].key == insertNode.key) {
            return false;
        }
        
        Node temp = table_1_[index];
        table_1_[index] = insertNode;
        return insertOccupied(temp, false);
    } else {
        if (table_2_[index].key == -1) {
            table_2_[index] = insertNode;
            return true;
        } else if (table_2_[index].key == insertNode.key) {
            return false;
        }
        
        Node temp = table_2_[index];
        table_2_[index] = insertNode;
        return insertOccupied(temp, true);
    }
}

bool HashCuckooTable::canInsertOccupied(HashCuckooTable::Node &insertNode,
                                        bool isInsertingInFirstTable,
                                        std::unordered_set<int> &visitedFirst,
                                        std::unordered_set<int> &visitedSecond) {
    if (isInsertingInFirstTable) {
        if (visitedFirst.find(insertNode.hash1) != visitedFirst.end()) {
            return false;
        }
        visitedFirst.insert(insertNode.hash1);
    }
    else {
        if (visitedSecond.find(insertNode.hash2) != visitedSecond.end()) {
            return false;
        }
        visitedSecond.insert(insertNode.hash2);
    }

    int index = isInsertingInFirstTable ? insertNode.hash1 : insertNode.hash2;
    if (isInsertingInFirstTable) {
        if (table_1_[index].key == -1 || table_1_[index].key == insertNode.key) {
            return true;
        }
        
        return canInsertOccupied(table_1_[index], false, visitedFirst, visitedSecond);
    } else {
        if (table_2_[index].key == -1 || table_2_[index].key == insertNode.key) {
            return true;
        }
        return canInsertOccupied(table_2_[index], true, visitedFirst, visitedSecond);
    }
}
bool HashCuckooTable::search(int key) {
    return searchImpl(key, hash1(key), true, 0) || searchImpl(key, hash2(key), false, 0);
}

bool HashCuckooTable::searchImpl(int key, int curIndex, bool isTable1, int elementsChecked) {
    if (elementsChecked > size_) {
        return false;
    }

    if (isTable1) {
        if (table_1_[curIndex].key == key) {
            return true;
        }
        if (table_1_[curIndex].key == -1) {
            return false;
        }
        return searchImpl(key, table_1_[curIndex].hash2, false, elementsChecked+1);
    } else {
        if (table_2_[curIndex].key == key) {
            return true;
        }
        if (table_2_[curIndex].key == -1) {
            return false;
        }
        return searchImpl(key, table_2_[curIndex].hash1, true, elementsChecked+1);
    }
}

void HashCuckooTable::rehash(int newSize) {
    std::vector<Node> elements;
    for (auto & el : table_1_) {
        if (el.key != -1) {
            elements.push_back(el);
        }
    }
    for (auto & el : table_2_) {
        if (el.key != -1) {
            elements.push_back(el);
        }
    }

    table_1_ = std::vector<Node>(newSize);
    table_2_ = std::vector<Node>(newSize);
    size_ = 0;
    for (auto & el : elements) {
        insert(el.key);
    }
}
void HashCuckooTable::print() {
    for (int i = 0; i < table_1_.size(); ++i) {
        std::cout << table_1_[i].key << ' ';
    }

    std::cout << '\n';
    for(int i = 0; i < table_2_.size(); ++i) {
        std::cout << table_2_[i].key << ' ';
    }
    std::cout << '\n';
}


