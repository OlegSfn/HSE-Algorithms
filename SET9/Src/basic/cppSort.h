#pragma once
#include <vector>
#include <string>

#include "../common/common.h"

template<class Comparator>
inline void cppSort(std::vector<std::string>& a, Comparator comparator) {
    std::sort(a.begin(), a.end(), comparator);
}