#include <iostream>
#include <array>
#include <algorithm>
#include <random>

#include "stringAdaptedSorters.h"

std::vector<std::string> msdRadixQuickSortImpl(std::vector<std::string>& R, size_t L) {
    if (R.size() <= 1) {
        return R;
    }

    if (R.size() < 74) {
        return ternaryQuickSortImpl(R, L);
    }

    std::vector<std::string> R_excl;
    std::vector<std::string> R_remaining;

    for (auto& s : R) {
        if (s.length() == L) {
            R_excl.emplace_back(std::move(s));
        } else if (s.length() > L) {
            R_remaining.emplace_back(std::move(s));
        }
    }

    if (R_remaining.empty()) {
        return R_excl;
    }

    auto buckets = countingSort(R_remaining, L);

    std::vector<std::string> result;
    result.reserve(R.size());
    result.insert(result.end(), std::make_move_iterator(R_excl.begin()), std::make_move_iterator(R_excl.end()));

    for (auto& bucket : buckets) {
        if (!bucket.empty()) {
            auto sorted_bucket = msdRadixQuickSortImpl(bucket, L + 1);
            result.insert(result.end(), std::make_move_iterator(sorted_bucket.begin()), std::make_move_iterator(sorted_bucket.end()));
        }
    }

    return result;
}

std::vector<std::string> msdRadixXQuickSort(std::vector<std::string>& R) {
    return msdRadixQuickSortImpl(R, 0);
}

std::vector<std::string> msdRadixQuickSortImplCountComparasings(std::vector<std::string>& R, size_t L) {
    if (R.size() <= 1) {
        return R;
    }

    if (R.size() < 74) {
        return ternaryQuickSortImplCountComparasings(R, L);
    }

    std::vector<std::string> R_excl;
    std::vector<std::string> R_remaining;

    for (auto& s : R) {
        if (s.length() == L) {
            R_excl.emplace_back(std::move(s));
        } else if (s.length() > L) {
            R_remaining.emplace_back(std::move(s));
        }
    }

    if (R_remaining.empty()) {
        return R_excl;
    }

    auto buckets = countingSortCountComparasings(R_remaining, L);

    std::vector<std::string> result;
    result.reserve(R.size());
    result.insert(result.end(), std::make_move_iterator(R_excl.begin()), std::make_move_iterator(R_excl.end()));

    for (auto& bucket : buckets) {
        if (!bucket.empty()) {
            auto sorted_bucket = msdRadixQuickSortImplCountComparasings(bucket, L + 1);
            result.insert(result.end(), std::make_move_iterator(sorted_bucket.begin()), std::make_move_iterator(sorted_bucket.end()));
        }
    }

    return result;
}

std::vector<std::string> msdRadixXQuickSortCountComparasings(std::vector<std::string>& R) {
    return msdRadixQuickSortImplCountComparasings(R, 0);
}