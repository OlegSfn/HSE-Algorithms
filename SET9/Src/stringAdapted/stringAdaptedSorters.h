#pragma once
#include <vector>
#include <string>

#include "../common/common.h"

std::vector<std::pair<std::string, int>> stringMergeSort(const std::vector<std::string>& strings);
std::vector<std::string> ternaryQuickSort(std::vector<std::string>& R);
std::vector<std::string> msdRadixSort(std::vector<std::string>& R);
std::vector<std::string> msdRadixXQuickSort(std::vector<std::string>& R);

std::vector<std::pair<std::string, int>> stringMergeSortCountComparasings(const std::vector<std::string>& strings);
std::vector<std::string> ternaryQuickSortCountComparasings(std::vector<std::string>& R);
std::vector<std::string> msdRadixSortCountComparasings(std::vector<std::string>& R);
std::vector<std::string> msdRadixXQuickSortCountComparasings(std::vector<std::string>& R);


std::vector<std::string> ternaryQuickSortImpl(std::vector<std::string>& R, size_t L);
std::vector<std::vector<std::string>> countingSort(std::vector<std::string>& R, size_t L);

std::vector<std::string> ternaryQuickSortImplCountComparasings(std::vector<std::string>& R, size_t L);
std::vector<std::vector<std::string>> countingSortCountComparasings(std::vector<std::string>& R, size_t L);