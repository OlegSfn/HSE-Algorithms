#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <random>

std::vector<std::string> ternaryQuickSortImpl(std::vector<std::string>& R, size_t L) {
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

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, R_remaining.size() - 1);
    size_t pivot_idx = dist(rng);
    char pivot = R_remaining[pivot_idx][L];

    std::vector<std::string> R_less, R_equal, R_great;

    for (auto& s : R_remaining) {
        if (s[L] < pivot) {
            R_less.emplace_back(std::move(s));
        } else if (s[L] == pivot) {
            R_equal.emplace_back(std::move(s));
        } else {
            R_great.emplace_back(std::move(s));
        }
    }

    R_less = ternaryQuickSortImpl(R_less, L);
    R_equal = ternaryQuickSortImpl(R_equal, L + 1);
    R_great = ternaryQuickSortImpl(R_great, L);

    std::vector<std::string> result;
    result.reserve(R.size());

    result.insert(result.end(), std::make_move_iterator(R_excl.begin()), std::make_move_iterator(R_excl.end()));

    result.insert(result.end(), std::make_move_iterator(R_less.begin()), std::make_move_iterator(R_less.end()));
    result.insert(result.end(), std::make_move_iterator(R_equal.begin()), std::make_move_iterator(R_equal.end()));
    result.insert(result.end(), std::make_move_iterator(R_great.begin()), std::make_move_iterator(R_great.end()));

    return result;
}

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


int main() {
    int n;
    std::cin >> n;

    std::cin.ignore();

    std::vector<std::string> strings(n);

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, strings[i]);
    }

    if (strings.empty()) {
        return 0;
    }

    auto sortedStrings = msdRadixXQuickSort(strings);
    for (const auto& str : sortedStrings) {
        std::cout << str << '\n';
    }

    return 0;
}