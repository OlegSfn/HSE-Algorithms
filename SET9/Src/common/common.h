#pragma once

#include <string_view>

inline size_t comparasingCount = 0;

inline bool CompareStringsLess(const std::string_view& a, const std::string_view& b) {
  for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
    if (a[i] != b[i]) {
      return a[i] < b[i];
    }
  }

  return a.size() < b.size();
}

inline bool CompareStringsLessCountComparasings(const std::string_view& a, const std::string_view& b) {
  for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
    ++comparasingCount;
    if (a[i] != b[i]) {
      ++comparasingCount;
      return a[i] < b[i];
    }
  }

  return a.size() < b.size();
}


inline bool CompareCharLessCountComparasings(char a, char b) {
  ++comparasingCount;
  return a < b;
}