#include <algorithm>
#include <iostream>
#include <array>

#include "stringAdaptedSorters.h"

std::vector<std::vector<std::string>> countingSort(std::vector<std::string>& R, size_t L) {
    const int ALPHABET_SIZE = 256;
    std::array<int, ALPHABET_SIZE> count = {};

    for (const auto& s : R) {
        if (s.length() > L) {
            unsigned char ch = s[L];
            ++count[ch];
        }
    }

    std::vector<std::vector<std::string>> buckets(ALPHABET_SIZE);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (count[i] > 0) {
            buckets[i].reserve(count[i]);
        }
    }

    for (auto& s : R) {
        if (s.length() > L) {
            unsigned char ch = s[L];
            buckets[ch].emplace_back(std::move(s));
        }
    }

    return buckets;
}

std::vector<std::string> msdRadixSortImpl(std::vector<std::string>& R, size_t L) {
    if (R.size() <= 1) {
        return R;
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
            auto sorted_bucket = msdRadixSortImpl(bucket, L + 1);
            result.insert(result.end(), std::make_move_iterator(sorted_bucket.begin()), std::make_move_iterator(sorted_bucket.end()));
        }
    }

    return result;
}

std::vector<std::string> msdRadixSort(std::vector<std::string>& R) {
    return msdRadixSortImpl(R, 0);
}


std::vector<std::vector<std::string>> countingSortCountComparasings(std::vector<std::string>& R, size_t L) {
    const int ALPHABET_SIZE = 256;
    std::array<int, ALPHABET_SIZE> count = {};

    for (const auto& s : R) {
        if (s.length() > L) {
            unsigned char ch = s[L];
            ++comparasingCount;
            ++count[ch];
        }
    }

    std::vector<std::vector<std::string>> buckets(ALPHABET_SIZE);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (count[i] > 0) {
            buckets[i].reserve(count[i]);
        }
    }

    for (auto& s : R) {
        if (s.length() > L) {
            unsigned char ch = s[L];
            buckets[ch].emplace_back(std::move(s));
        }
    }

    return buckets;
}

std::vector<std::string> msdRadixSortImplCountComparasings(std::vector<std::string>& R, size_t L) {
    if (R.size() <= 1) {
        return R;
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
            auto sorted_bucket = msdRadixSortImplCountComparasings(bucket, L + 1);
            result.insert(result.end(), std::make_move_iterator(sorted_bucket.begin()), std::make_move_iterator(sorted_bucket.end()));
        }
    }

    return result;
}

std::vector<std::string> msdRadixSortCountComparasings(std::vector<std::string>& R) {
    return msdRadixSortImplCountComparasings(R, 0);
}