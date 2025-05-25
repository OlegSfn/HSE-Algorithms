#include "../basic/basic.h"
#include "../stringAdapted/stringAdaptedSorters.h"

#include <iostream>
#include <fstream>
#include <random>

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
    std::string alphabet_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#%:;^&*()-";
    std::uniform_int_distribution<size_t> alphabetDist_;
};


template<typename T>
void PrintArrayIntoFile(std::ofstream& file, const std::vector<T>& array) {
  for (size_t i = 0; i < array.size(); ++i) {
    file << array[i];
    if (i < array.size() - 1) {
      file << ", ";
    }
  }
  file << '\n';
}


class StringSortTester {
 public:
    StringSortTester(size_t startArraySize, size_t endArraySize, size_t step, size_t minStringLength, size_t maxStringLength, float unsortedCoeff, size_t timesOfComputations)
    : startArraySize_(startArraySize)
    , endArraySize_(endArraySize)
    , step_(step)
    , minStringLength_(minStringLength)
    , maxStringLength_(maxStringLength)
    , unsortedCoeff_(unsortedCoeff)
    , timesOfComputations_(timesOfComputations)
    {}

  template<class SortFunc>
  double StopwatchSortFunction(std::vector<std::string>& array, int timesOfComputations, SortFunc sortFunction){
    double result = 0;
    for(size_t i = 0; i < timesOfComputations; ++i){
      std::vector<std::string> arrayCopy = array;
      auto start = std::chrono::high_resolution_clock::now();
      sortFunction(arrayCopy);
      auto end = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double, std::milli> duration = end - start;
      result += duration.count();
    }

    return result/timesOfComputations;
  }

  template<class SortFunc>
  void TestTime(SortFunc sortFunction, const std::string& outputFileName){
    StringGenerator stringGenerator;

    std::vector<std::string> rangeArray = stringGenerator.RandomArray(endArraySize_, minStringLength_, maxStringLength_);
    std::vector<std::string> reversedArray = stringGenerator.ReversedArray(endArraySize_, minStringLength_, maxStringLength_);
    std::vector<std::string> almostSortedArray = stringGenerator.AlmostSortedArray(endArraySize_, minStringLength_, maxStringLength_, unsortedCoeff_);

    std::vector<size_t> arraySizes;
    std::vector<double> rangeArrayDurations;
    std::vector<double> reversedArrayDurations;
    std::vector<double> almostSortedArrayDurations;
    for (size_t size = startArraySize_; size <= endArraySize_; size += step_) {
      std::vector<std::string> rangeSubArray(rangeArray.begin(), rangeArray.begin() + size);
      std::vector<std::string> reversedSubArray(reversedArray.begin(), reversedArray.begin() + size);
      std::vector<std::string> almostSortedSubArray(almostSortedArray.begin(), almostSortedArray.begin() + size);

      double rangeArrayTime = StopwatchSortFunction(rangeSubArray, timesOfComputations_, sortFunction);
      double reversedArrayTime = StopwatchSortFunction(reversedSubArray, timesOfComputations_, sortFunction);
      double almostSortedArrayTime = StopwatchSortFunction(almostSortedSubArray, timesOfComputations_, sortFunction);

      arraySizes.push_back(size);
      rangeArrayDurations.push_back(rangeArrayTime);
      reversedArrayDurations.push_back(reversedArrayTime);
      almostSortedArrayDurations.push_back(almostSortedArrayTime);
    }

    WriteResultsToFile(outputFileName, arraySizes, rangeArrayDurations, reversedArrayDurations, almostSortedArrayDurations);
  }

  template<class SortFunc>
  void TestCharCompares(SortFunc sortFunction, const std::string& outputFileName) {
    StringGenerator stringGenerator;

    std::vector<std::string> rangeArray = stringGenerator.RandomArrayWithPrefix(endArraySize_, minStringLength_, maxStringLength_);
    std::vector<std::string> reversedArray = stringGenerator.ReversedArrayWithPrefix(endArraySize_, minStringLength_, maxStringLength_);
    std::vector<std::string> almostSortedArray = stringGenerator.AlmostSortedArrayWithPrefix(endArraySize_, minStringLength_, maxStringLength_, unsortedCoeff_);

    std::vector<size_t> arraySizes;
    std::vector<size_t> rangeArrayCompares;
    std::vector<size_t> reversedArrayCompares;
    std::vector<size_t> almostSortedArrayCompares;
    for (size_t size = startArraySize_; size <= endArraySize_; size += step_) {
      std::vector<std::string> rangeSubArray(rangeArray.begin(), rangeArray.begin() + size);
      std::vector<std::string> reversedSubArray(reversedArray.begin(), reversedArray.begin() + size);
      std::vector<std::string> almostSortedSubArray(almostSortedArray.begin(), almostSortedArray.begin() + size);

        comparasingCount = 0;
        sortFunction(rangeSubArray);
        size_t rangeArrayCompareCount = comparasingCount;

        comparasingCount = 0;
        sortFunction(reversedSubArray);
        size_t reversedArrayCompareCount = comparasingCount;

        comparasingCount = 0;
        sortFunction(almostSortedSubArray);
        size_t almostSortedArrayCompareCount = comparasingCount;

        arraySizes.push_back(size);
        rangeArrayCompares.push_back(rangeArrayCompareCount);
        reversedArrayCompares.push_back(reversedArrayCompareCount);
        almostSortedArrayCompares.push_back(almostSortedArrayCompareCount);
    }

    WriteResultsToFile(outputFileName, arraySizes, rangeArrayCompares, reversedArrayCompares, almostSortedArrayCompares);
  }

  void WriteResultsToFile(const std::string& fileName, std::vector<size_t>& arraySizes, std::vector<double>& rangeArrayDurations, std::vector<double>& reversedArrayDurations, std::vector<double>& almostSortedArrayDurations) {
    std::ofstream file(fileName);
    PrintArrayIntoFile(file, arraySizes);
    PrintArrayIntoFile(file, rangeArrayDurations);
    PrintArrayIntoFile(file, reversedArrayDurations);
    PrintArrayIntoFile(file, almostSortedArrayDurations);
    file.close();
  }

  void WriteResultsToFile(const std::string& fileName, std::vector<size_t>& arraySizes, std::vector<size_t>& rangeArrayCompares, std::vector<size_t>& reversedArrayCompares, std::vector<size_t>& almostSortedArrayCompares) {
      std::ofstream file(fileName);
      PrintArrayIntoFile(file, arraySizes);
      PrintArrayIntoFile(file, rangeArrayCompares);
      PrintArrayIntoFile(file, reversedArrayCompares);
      PrintArrayIntoFile(file, almostSortedArrayCompares);
      file.close();
  }

private:
  size_t startArraySize_;
  size_t endArraySize_;
  size_t step_;
  size_t minStringLength_;
  size_t maxStringLength_;
  float unsortedCoeff_;
  size_t timesOfComputations_;
};

void TestTimeBasic(StringSortTester& sort_tester) {
  sort_tester.TestTime(
      [](std::vector<std::string>& vec)
      {
          quickSort(vec, std::less<>());
      },
      "./Basic/Time/DefaultComparator/quickSortDefaultComparator.txt");
  sort_tester.TestTime(
      [](std::vector<std::string>& vec)
      {
          mergeSort(vec, std::less<>());
      },
      "./Basic/Time/DefaultComparator/mergeSortDefaultComparator.txt");

  sort_tester.TestTime(
      [](std::vector<std::string>& vec)
      {
         cppSort(vec, std::less<>());
      },
      "./Basic/Time/DefaultComparator/cppSortDefaultComparator.txt");
  sort_tester.TestTime(
      [](std::vector<std::string>& vec)
      {
        introSort(vec, std::less<>());
      },
      "./Basic/Time/DefaultComparator/introSortDefaultComparator.txt");
}

void TestTimeBasicComp(StringSortTester& sort_tester) {
    sort_tester.TestTime(
        [](std::vector<std::string>& vec)
        {
          quickSort(vec, CompareStringsLess);
        },
        "./Basic/Time/MyComparator/quickSortMyComparator.txt");
    sort_tester.TestTime(
        [](std::vector<std::string>& vec)
        {
          mergeSort(vec, CompareStringsLess);
        },
        "./Basic/Time/MyComparator/mergeSortMyComparator.txt");

    sort_tester.TestTime(
        [](std::vector<std::string>& vec)
        {
          cppSort(vec, CompareStringsLess);
        },
        "./Basic/Time/MyComparator/cppSortMyComparator.txt");
    sort_tester.TestTime(
        [](std::vector<std::string>& vec)
        {
          introSort(vec, CompareStringsLess);
        },
        "./Basic/Time/MyComparator/introSortMyComparator.txt");
}

void TestComparesBasic(StringSortTester& sort_tester) {
    sort_tester.TestCharCompares(
        [](std::vector<std::string>& vec)
        {
          quickSort(vec, CompareStringsLessCountComparasings);
        },
        "./Basic/Comparasings/quickSortComparasings.txt");
    sort_tester.TestCharCompares(
        [](std::vector<std::string>& vec)
        {
          mergeSort(vec, CompareStringsLessCountComparasings);
        },
        "./Basic/Comparasings/mergeSortCompasings.txt");

    sort_tester.TestCharCompares(
        [](std::vector<std::string>& vec)
        {
          cppSort(vec, CompareStringsLessCountComparasings);
        },
        "./Basic/Comparasings/cppSortComparasings.txt");
    sort_tester.TestCharCompares(
        [](std::vector<std::string>& vec)
        {
          introSort(vec, CompareStringsLessCountComparasings);
        },
        "./Basic/Comparasings/introSortComparasings.txt");
}

void TestStringAdapted(StringSortTester& sort_tester) {
  sort_tester.TestTime(stringMergeSort, "./StringAdapted/Time/stringMergeSort.txt");
  sort_tester.TestTime(ternaryQuickSort, "./StringAdapted/Time/ternaryQuickSort.txt");
  sort_tester.TestTime(msdRadixSort, "./StringAdapted/Time/msdRadixSort.txt");
  sort_tester.TestTime(msdRadixXQuickSort, "./StringAdapted/Time/msdRadixXQuickSort.txt");
}

void TestStringAdaptedCompares(StringSortTester& sort_tester) {
  sort_tester.TestCharCompares(stringMergeSortCountComparasings, "./StringAdapted/Comparasings/stringMergeSort.txt");
  sort_tester.TestCharCompares(ternaryQuickSortCountComparasings, "./StringAdapted/Comparasings/ternaryQuickSort.txt");
  sort_tester.TestCharCompares(msdRadixSortCountComparasings, "./StringAdapted/Comparasings/msdRadixSort.txt");
  sort_tester.TestCharCompares(msdRadixXQuickSortCountComparasings, "./StringAdapted/Comparasings/msdRadixXQuickSort.txt");
}

int main() {
  StringSortTester sort_tester(100, 3000, 100, 10, 200, 0.1, 100);
   TestTimeBasic(sort_tester);
   TestTimeBasicComp(sort_tester);
   TestComparesBasic(sort_tester);

   TestStringAdapted(sort_tester);
   TestStringAdaptedCompares(sort_tester);
   
  return 0;
}