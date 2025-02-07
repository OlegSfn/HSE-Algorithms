#include "SkipList/SkipList.h"
#include "RBTree//RBTree.h"
#include <iostream>
#include <random>

std::vector<int> GenerateKeys(int numKeys) {
    std::vector<int> keys(numKeys);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    for(int i = 0; i < numKeys; ++i) {
        keys[i] = dist(gen);
    }

    return keys;
}

void Test() {
    for(int i = 1000; i < 100000; i += 1000) {
        std::vector<int> keys = GenerateKeys(i);
        SkipList skipList(keys);
        RBTree rbTree(keys);
        
        int rbTreeWins = 0, skipListsWins = 0, ties = 0;
        for(int key : keys) {
            auto [skipListContains, skipListOperations] = skipList.contains(key);
            auto [rbTreeContains, rbTreeOperations] = rbTree.find(key);
            if (skipListOperations < rbTreeOperations) {
                ++skipListsWins;
            } else if (skipListOperations > rbTreeOperations) {
                ++rbTreeWins;
            } else {
                ++ties;
            }
        }
        
        std::cout << "Number of keys: " << i << '\n';
        std::cout << "SkipList wins: " << skipListsWins << '\n';
        std::cout << "RBTree wins: " << rbTreeWins << '\n';
        std::cout << "Ties: " << ties << '\n';
        std::cout << "SkipLists win/all " << (double)skipListsWins / i << '\n';
    }
}


int main() {
    Test();
    return 0;
}
