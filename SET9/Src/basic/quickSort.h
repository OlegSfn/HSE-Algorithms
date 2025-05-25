#pragma once
#include <vector>
#include <string>

#include "../common/common.h"

template<class Comparator>
void quickSortImpl(std::vector<std::string>& a, int begin, int end, Comparator comparator) {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<size_t> dist(begin, end-1);

  std::string pivot = a[dist(rng)];
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
    quickSortImpl(a, begin, j + 1, comparator);
  }
  if (i < end){
    quickSortImpl(a, i, end, comparator);
  }
}


template<class Comparator>
void quickSort(std::vector<std::string>& a, Comparator comparator) {
  if (a.size() < 2){
      return;
  }

  quickSortImpl(a, 0, a.size(), comparator);
}