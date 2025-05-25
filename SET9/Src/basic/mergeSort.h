#pragma once
#include <vector>
#include <string>

#include "../common/common.h"

template<class Comparator>
std::vector<std::string> merge(std::vector<std::string>& a, std::vector<std::string>& b, Comparator comparator) {
    std::vector<std::string> result;
    result.reserve(a.size() + b.size());

    int i = 0;
    int j = 0;
    while (i < a.size() && j < b.size()) {
        if (comparator(a[i], b[j])) {
            result.emplace_back(std::move(a[i++]));
        } else {
            result.emplace_back(std::move(b[j++]));
        }
    }

    while (i < a.size()) {
        result.emplace_back(std::move(a[i++]));
    }

    while (j < b.size()) {
        result.emplace_back(std::move(b[j++]));
    }

    return result;
}


template<class Comparator>
std::vector<std::string> mergeSortImpl(std::vector<std::string>& strings, int left, int right, Comparator comparator) {
    if (left == right) {
        return {strings[left]};
    }

    int mid = left + (right - left) / 2;
    auto leftSorted = mergeSortImpl(strings, left, mid, comparator);
    auto rightSorted = mergeSortImpl(strings, mid + 1, right, comparator);

    return merge(leftSorted, rightSorted, comparator);
}

template<class Comparator>
std::vector<std::string> mergeSort(std::vector<std::string>& strings, Comparator comparator) {
    return mergeSortImpl(strings, 0, strings.size() - 1, comparator);
}
