#include "HashLPTable.h"
#include "HashCuckooTable.h"
#include <iostream>

void TestHashLPTable() {
    HashLPTable table(3);

    table.insert(1);
    table.insert(2);
    table.insert(3);
    table.insert(13);
    table.insert(12);
    table.remove(2);
    std::cout << table.search(12) << std::endl;

    table.print();
    std::cout << table.size();
}

void TestCuckooTable() {
    std::vector<int> elements{20, 50, 53, 75, 100, 67, 105, 3, 36, 39, 6};
    HashCuckooTable table(11);
    for (auto el : elements) {
        std::cout << "Inserting: " << el << '\n';
        table.insert(el);
        table.print();

        std::cout << "\n\n";
    }

    std::cout << table.search(50) << std::endl;
}

int main() {
//    TestCuckooTable();
    HashLPTable table(10);
    std::vector<int>a{2,1,12,11,22,21,32,31};
    for(int el : a) {
        table.insert(el);
    }

    table.print();

    return 0;
}
