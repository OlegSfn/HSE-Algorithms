#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include <iostream>
#include <utility>
#include <string_view>

std::pair<int, int> lcpCompare(std::string_view a, std::string_view b, int k) {
    int min_length = std::min(a.length(), b.length());
    int i;

    for (i = k; i < min_length; i++) {
        if (a[i] < b[i]) {
            return {-1, i};
        } else if (a[i] > b[i]) {
            return {1, i};
        }
    }

    if (a.length() == b.length()) {
        return {0, i};
    }
    return {a.length() < b.length() ? -1 : 1, i};
}

std::vector<std::pair<std::string, int>> stringMerge(std::vector<std::pair<std::string, int>>& P, std::vector<std::pair<std::string, int>>& Q) {
    std::vector<std::pair<std::string, int>> R;
    R.reserve(P.size() + Q.size());
    int i = 0, j = 0;
    int m = P.size(), f = Q.size();

    while (i < m && j < f) {
        int& ki = P[i].second;
        int& pj = Q[j].second;

        if (ki > pj) {
            R.emplace_back(std::move(P[i]));
            ++i;
        } else if (ki < pj) {
            R.emplace_back(std::move(Q[j]));
            ++j;
        } else {
            const auto& [cmp, h] = lcpCompare(P[i].first, Q[j].first, ki);

            if (cmp < 0) {
                R.emplace_back(std::move(P[i]));
                ++i;
                pj = h;
            } else {
                R.emplace_back(std::move(Q[j]));
                ++j;
                ki = h;
            }
        }
    }

    while (i < m) {
        R.emplace_back(std::move(P[i]));
        ++i;
    }

    while (j < f) {
        R.emplace_back(std::move(Q[j]));
        ++j;
    }

    return R;
}

std::vector<std::pair<std::string, int>> stringMergeSortImpl(const std::vector<std::string>& strings, int left, int right) {
    if (left == right) {
        return {{strings[left], 0}};
    }

    int mid = left + (right - left) / 2;

    auto P = stringMergeSortImpl(strings, left, mid);
    auto Q = stringMergeSortImpl(strings, mid + 1, right);

    return stringMerge(P, Q);
}

std::vector<std::pair<std::string, int>> stringMergeSort(const std::vector<std::string>& strings) {
    return stringMergeSortImpl(strings, 0, strings.size() - 1);
}

int main() {
    int n;
    std::cin >> n;

    std::cin.ignore();

    std::vector<std::string> strings(n);

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, strings[i]);
    }

    if (strings.empty()) {
        return 0;
    }

    auto sortedStrings = stringMergeSort(strings);
    for (const auto& [str, _] : sortedStrings) {
        std::cout << str << '\n';
    }

    return 0;
}