#include <iostream>
#include <vector>
#include <cassert>

std::string get_string_by_prefix(const std::vector<int>& prefs) {
    std::string str (prefs.size(), '\0');
    char current_symbol = 'a';
    for (int i = 0; i < prefs.size(); ++i) {
        if (prefs[i] > 0) {
            str[i] = str[prefs[i] - 1];
        } else {
            str[i] = ++current_symbol;
        }
    }
    return str;
}

std::vector<int> z_f(const std::string& s) {
    int n = s.length();
    std::vector<int> z(n, 0);

    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

std::vector<int> prefix_f(const std::string& s) {
    int n = s.length();
    std::vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }

        pi[i] = j;
    }

    return pi;
}

std::vector<int> z_to_prefix(const std::vector<int>& z) {
    int n = z.size();
    std::vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        // z[i] > 0 => s[i...i+z[i]-1] = s[0...z[i]-1]
        if (z[i] > 0) {
            for (int j = 0; j < z[i] && i + j < n; ++j) {
                if (j + 1 > pi[i + j]) {
                    pi[i + j] = j + 1;
                }
            }
        }
    }

    return pi;
}

std::vector<int> prefix_to_z(const std::vector<int>& prefs) {
    return z_f(get_string_by_prefix(prefs));
}


void test(const std::string& s) {
    std::cout << "Testing string: " << s << '\n';

    std::vector<int> original_z = z_f(s);
    std::vector<int> original_pi = prefix_f(s);

    std::vector<int> pi_from_z = z_to_prefix(original_z);
    std::vector<int> z_from_pi = prefix_to_z(original_pi);

    std::cout << "Z func:\t";
    for (int val : original_z) std::cout << val << " ";
    std::cout << '\n';

    std::cout << "Pref func:\t";
    for (int val : original_pi) std::cout << val << " ";
    std::cout << '\n';

    std::cout << "Z -> Pref:\t";
    for (int val : pi_from_z) std::cout << val << " ";
    std::cout << '\n';

    std::cout << "Pref -> Z:\t";
    for (int val : z_from_pi) std::cout << val << " ";
    std::cout << '\n';

    bool pi_correct = original_pi == pi_from_z;
    bool z_correct = original_z == z_from_pi;

    std::cout << "Is correct pi? " << (pi_correct ? "yes" : "no") << '\n';
    std::cout << "Is correct z? " << (z_correct ? "yes" : "no") << '\n';
    std::cout << '\n';
}


int main() {
    test("ababaca");
    test("aabaaab");
    test("abacaba");
    test("aaaaa");
    test("abcdef");
    test("aabbaabb");

    return 0;
}