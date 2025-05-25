#include <random>
#include <iostream>
#include <vector>
#include <string>

#include "../basic/basic.h"
#include "../common/common.h"
#include "../stringAdapted/stringAdaptedSorters.h"


class StringGenerator {
public:
    StringGenerator() : gen_(std::random_device{}()), alphabetDist_(0, alphabet_.size()) {}

    std::vector<std::string> RandomArray(size_t arraySize, size_t minStringLength, size_t maxStringLength) {
        std::vector<std::string> result(arraySize);

        for (auto& s : result) {
            std::uniform_int_distribution<size_t> stringSizeDist(minStringLength, maxStringLength);
            s.resize(stringSizeDist(gen_));

            for (auto& c : s) {
                c = alphabet_[alphabetDist_(gen_)];
            }
        }

        return result;
    }

    std::vector<std::string> ReversedArray(size_t arraySize, size_t minStringLength, size_t maxStringLength) {
        std::vector<std::string> result = AlmostSortedArray(arraySize, minStringLength, maxStringLength, 0);
        std::reverse(result.begin(), result.end());

        return result;
    }

    std::vector<std::string> AlmostSortedArray(size_t arraySize, size_t minStringLength, size_t maxStringLength, float unsortedCoeff) {
        std::vector<std::string> result = RandomArray(arraySize, minStringLength, maxStringLength);
        std::sort(result.begin(), result.end());

        std::uniform_int_distribution<size_t> indexDist(0, result.size() - 1);
        for (size_t i = 0; i < result.size() * unsortedCoeff; ++i) {
            std::swap(result[i], result[indexDist(gen_)]);
        }

        return result;
    }

    std::vector<std::string> RandomArrayWithPrefix(size_t arraySize, size_t minStringLength, size_t maxStringLength) {
        std::vector<std::string> result = RandomArray(arraySize, minStringLength, maxStringLength);
        std::string prefix(500, 'a');
        for (auto& s : result) {
            s = prefix + s;
        }

        return result;
    }

    std::vector<std::string> ReversedArrayWithPrefix(size_t arraySize, size_t minStringLength, size_t maxStringLength) {
        std::vector<std::string> result = AlmostSortedArrayWithPrefix(arraySize, minStringLength, maxStringLength, 0);
        std::reverse(result.begin(), result.end());

        return result;
    }

    std::vector<std::string> AlmostSortedArrayWithPrefix(size_t arraySize, size_t minStringLength, size_t maxStringLength, float unsortedCoeff) {
        std::vector<std::string> result = RandomArrayWithPrefix(arraySize, minStringLength, maxStringLength);
        std::sort(result.begin(), result.end());

        std::uniform_int_distribution<size_t> indexDist(0, result.size() - 1);
        for (size_t i = 0; i < result.size() * unsortedCoeff; ++i) {
            std::swap(result[i], result[indexDist(gen_)]);
        }

        return result;
    }

private:
    std::mt19937 gen_;
    std::string alphabet_ = "!@#%:;^&*()-";
    std::uniform_int_distribution<size_t> alphabetDist_;
};

void CompareArrays(std::vector<std::string>& arr1, std::vector<std::string>& arr2) {
    if (arr1 != arr2) {
        for(auto& el : arr1) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        for(auto& el : arr2) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
        std::cout << "Failed" << std::endl;
    }
}


void TestCppSort(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2, std::vector<std::string>& arr3) {
    cppSort(arr1, std::less<std::string>());
    CompareArrays(arr1, sorted);

    cppSort(arr2, CompareStringsLess);
    CompareArrays(arr2, sorted);

    cppSort(arr3, CompareStringsLessCountComparasings);
    CompareArrays(arr3, sorted);
}

void TestIntroSort(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2, std::vector<std::string>& arr3) {
    introSort(arr1, std::less<std::string>());
    CompareArrays(arr1, sorted);

    introSort(arr2, CompareStringsLess);
    CompareArrays(arr2, sorted);

    introSort(arr3, CompareStringsLessCountComparasings);
    CompareArrays(arr3, sorted);
}

void TestMergeSort(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2, std::vector<std::string>& arr3) {
    arr1 = mergeSort(arr1, std::less<std::string>());
    CompareArrays(arr1, sorted);

    arr2 = mergeSort(arr2, CompareStringsLess);
    CompareArrays(arr2, sorted);

    arr3 = mergeSort(arr3, CompareStringsLessCountComparasings);
    CompareArrays(arr3, sorted);
}

void TestQuickSort(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2, std::vector<std::string>& arr3) {
    quickSort(arr1, std::less<std::string>());
    CompareArrays(arr1, sorted);

    quickSort(arr2, CompareStringsLess);
    CompareArrays(arr2, sorted);

    quickSort(arr3, CompareStringsLessCountComparasings);
    CompareArrays(arr3, sorted);
}

void TestMergeSortStringAdapted(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2) {
    auto resBasic = stringMergeSort(arr1);
    std::vector<std::string> compareResBasic;

    for (auto& el : resBasic) {
        compareResBasic.push_back(std::move(el.first));
    }

    CompareArrays(compareResBasic, sorted);

    auto resAdapted = stringMergeSortCountComparasings(arr2);
    std::vector<std::string> compareResAdapted;
    for (auto& el : resAdapted) {
        compareResAdapted.push_back(std::move(el.first));
    }

    CompareArrays(compareResAdapted, sorted);
}

void TestMSDRadixSort(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2) {
    auto resBasic = msdRadixSort(arr1);
    CompareArrays(resBasic, sorted);

    auto resAdapted = msdRadixSortCountComparasings(arr2);
    CompareArrays(resAdapted, sorted);
}

void TestMSDRadixSortXQuickSort(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2) {
    auto resBasic = msdRadixXQuickSort(arr1);
    CompareArrays(resBasic, sorted);

    auto resAdapted = msdRadixXQuickSortCountComparasings(arr2);
    CompareArrays(resAdapted, sorted);
}

void TestQuickSortStringAdapted(std::vector<std::string>& sorted, std::vector<std::string>& arr1, std::vector<std::string>& arr2) {
    auto resBasic = ternaryQuickSort(arr1);
    CompareArrays(resBasic, sorted);

    auto resAdapted = ternaryQuickSortCountComparasings(arr2);
    CompareArrays(resAdapted, sorted);
}


int main() {
    int tests = 10000;

    while(tests--) {
        std::vector<std::string> arr1 = StringGenerator().RandomArray(1000, 10, 15);
        auto arr2 = arr1;
        // auto arr3 = arr1;
        auto sorted = arr1;

        std::sort(sorted.begin(), sorted.end());

        // TestCppSort(sorted, arr1, arr2, arr3);
        // TestIntroSort(sorted, arr1, arr2, arr3);
        // TestMergeSort(sorted, arr1, arr2, arr3);
        // TestQuickSort(sorted, arr1, arr2, arr3);

        // TestMergeSortStringAdapted(sorted, arr1, arr2);
        // TestMSDRadixSort(sorted, arr1, arr2);
        // TestMSDRadixSortXQuickSort(sorted, arr1, arr2);
        TestQuickSortStringAdapted(sorted, arr1, arr2);
    }

    return 0;
}