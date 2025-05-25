#pragma once
#include <vector>
#include <string>
#include <random>

#include "../common/common.h"

template<class Comparator>
void heapify(std::vector<std::string>& a, int n, int i, int begin, Comparator comparator){
  int largest = i;
  int left = 2 * (i - begin) + 1 + begin;
  int right = 2 * (i - begin) + 2 + begin;

  if (left < begin + n && comparator(a[largest],a[left])) {
    largest = left;
  }

  if (right < begin + n && comparator(a[largest], a[right])) {
    largest = right;
  }

  if (largest != i) {
    std::swap(a[i], a[largest]);
    heapify(a, n, largest, begin, comparator);
  }
}

template<class Comparator>
void heapSort(std::vector<std::string>& a, int begin, int end, Comparator comparator){
  int n = end - begin;
  for (int i = begin + n / 2 - 1; i >= begin; --i){
    heapify(a, n, i, begin, comparator);
  }
  for (int i = end - 1; i > begin; --i){
    std::swap(a[begin], a[i]);
    heapify(a, i - begin, begin, begin, comparator);
  }
}


template<class Comparator>
void insertionSort(std::vector<std::string>& a, int begin, int end, Comparator comparator){
  for (int i = begin + 1; i < end; ++i){
    int j = i - 1;
    while(j >= begin && comparator(a[j+1], a[j])) {
      std::swap(a[j], a[j+1]);
      --j;
    }
  }
}


template<class Comparator>
void introSortImpl(std::vector<std::string>& a, int begin, int end, int maxDepth, Comparator comparator){
  if (end - begin < 16){
    insertionSort(a, begin, end, comparator);
    return;
  }

  if (maxDepth == 0){
    heapSort(a, begin, end, comparator);
    return;
  }

  std::random_device rand_dev;
  std::uniform_int_distribution<int> distribution(begin, end-1);
  std::string pivot = a[distribution(rand_dev)];
  int i = begin;
  int j = end - 1;

  while(i <= j){
    while(comparator(a[i], pivot)){
      ++i;
    }
    while(comparator(pivot, a[j])){
      --j;
    }
    if (i <= j){
      std::swap(a[i], a[j]);
      ++i;
      --j;
    }
  }

  if (begin < j){
    introSortImpl(a, begin, j + 1, maxDepth - 1, comparator);
  }
  if (i < end){
    introSortImpl(a, i, end, maxDepth - 1, comparator);
  }
}


template<class Comparator>
void introSort(std::vector<std::string>& a, Comparator comparator) {
  if (a.size() < 2){
    return;
  }

  int maxDepth = 2 * std::log2(a.size());
  introSortImpl(a, 0, a.size(), maxDepth, comparator);
}
