#include "SkipList.h"
#include <iostream>

SkipList::SkipList(const std::vector<int>& keys) {
    if (keys.empty()){
        return;
    }

    std::vector<Node*> lines;
    // first level
    {
        Node* cur_head = new Node(INT_MIN);
        Node* prev = cur_head;
        for (int key : keys) {
            Node* cur = new Node(key);
            prev->rightNeighbour = cur;
            prev = cur;
        }
        prev->rightNeighbour = new Node(INT_MAX);
        lines.push_back(cur_head);
    }

    levels = 1;
    // other levels
    while (lines.back()->rightNeighbour->rightNeighbour->rightNeighbour) {
        Node* cur_head = new Node(INT_MIN);
        Node* prev = cur_head;
        cur_head->downNeighbour = lines.back();

        Node* prev_line = lines.back()->rightNeighbour;
        int i = 0;
        while (prev_line->rightNeighbour != nullptr) {
            if (i % 2 != 0) {
                Node* cur = new Node(prev_line->key);
                cur->downNeighbour = prev_line;
                prev->rightNeighbour = cur;
                prev = cur;
            }
            prev_line = prev_line->rightNeighbour;
            ++i;
        }

        prev->rightNeighbour = new Node(INT_MAX);
        lines.push_back(cur_head);
        ++levels;
    }

    head = lines.back();
}

SkipList::~SkipList() {
    Node* cur = head;
    while(cur) {
        Node* next = cur->downNeighbour;
        delete cur;
        cur = next;
    }
}

std::pair<bool,int> SkipList::contains(int key) {
    Node* cur = head;
    int operations = 0;

    while (cur) {
        Node* next = cur->rightNeighbour;
        while (next->rightNeighbour && next->key < key) {
            next = next->rightNeighbour;
            ++operations;
        }

        if (next->key == key) {
            return {true, operations};
        }

        cur = cur->downNeighbour;
    }

    return {false, operations};
}

void SkipList::print() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->rightNeighbour;
        while (next->rightNeighbour) {
            std::cout << next->key << " ";
            next = next->rightNeighbour;
        }
        std::cout << '\n';
        cur = cur->downNeighbour;
    }
}


