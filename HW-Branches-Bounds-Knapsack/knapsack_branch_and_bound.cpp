#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

struct Item {
    std::string name;
    double weight;
    double value;
    double valuePerWeight;

    Item(std::string name, double w, double v) : name(name), weight(w), value(v) {
        valuePerWeight = static_cast<double>(v) / w;
    }
};

struct Node {
    int level;
    double value;
    double weight;
    double bound;
    std::vector<bool> selected;

    Node() : level(-1), value(0.0), weight(0.0), bound(0.0) {}
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.bound < b.bound;
    }
};

double calculateBound(Node node, int n, int capacity, const std::vector<Item>& items) {
    if (node.weight >= capacity) {
        return 0;
    }

    double bound = node.value;
    int j = node.level + 1;
    int totalWeight = node.weight;

    while (j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        bound += items[j].value;
        j++;
    }

    if (j < n) {
        bound += (capacity - totalWeight) * items[j].valuePerWeight;
    }

    return bound;
}

std::pair<int, std::vector<Item>> knapsackBranchesAndBounds(std::vector<Item>& items, int capacity) {
    int n = items.size();

    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.valuePerWeight > b.valuePerWeight;
    });

    std::priority_queue<Node, std::vector<Node>, CompareNode> pq;

    Node u, v;
    u.selected.resize(n, false);
    u.bound = calculateBound(u, n, capacity, items);

    pq.push(u);

    double maxValue = 0;
    std::vector<bool> bestSolution(n, false);

    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        v.level = u.level + 1;
        if (v.level >= n) {
            continue;
        }

        v.weight = u.weight + items[v.level].weight;
        v.value = u.value + items[v.level].value;
        v.selected = u.selected;
        v.selected[v.level] = true;

        if (v.weight <= capacity && v.value > maxValue) {
            maxValue = v.value;
            bestSolution = v.selected;
        }

        v.bound = calculateBound(v, n, capacity, items);
        if (v.bound > maxValue) {
            pq.push(v);
        }

        v.weight = u.weight;
        v.value = u.value;
        v.selected = u.selected;
        v.selected[v.level] = false;

        v.bound = calculateBound(v, n, capacity, items);
        if (v.bound > maxValue) {
            pq.push(v);
        }
    }

    std::vector<Item> selectedItems;
    for (int i = 0; i < n; i++) {
        if (bestSolution[i]) {
            selectedItems.emplace_back(items[i]);
        }
    }

    return {maxValue, selectedItems};
}

int main() {
    std::vector<Item> items = {
        {"1", 2.0,    40},
        {"2", 3.14,   50},
        {"3", 1.98,   100},
        {"4", 5.0,    95},
        {"5", 3.0,    30},
    };

    int capacity = 15;

    auto start = std::chrono::steady_clock::now();
    auto [maxValue, selectedItems] = knapsackBranchesAndBounds(items, capacity);
    auto diff = std::chrono::steady_clock::now() - start;
    std::cout << "Отработал за: " << std::chrono::duration<double, std::milli>(diff).count() << " мс\n";

    double totalValue = 0;
    for (const auto& item : selectedItems) {
        totalValue += item.value;
    }

    std::cout << "Максимальная полезность: " << totalValue << "\n\n";
    std::cout << "\nВыбранные предметы:\n";
    for (const auto& item : selectedItems) {
        std::cout << "Имя: " << item.name << " вес: " << item.weight << " цена: " << item.value << '\n';
    }

    return 0;
}