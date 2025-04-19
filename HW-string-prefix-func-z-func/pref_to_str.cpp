#include <iostream>
#include <vector>
#include <string>
#include <cassert>

std::string get_string_by_prefix(const std::vector<int>& prefs) {
    std::string str (prefs.size(), '\0');
    char current_symbol = 'a' - 1;
    for (int i = 0; i < prefs.size(); ++i) {
        if (prefs[i] > 0) {
            str[i] = str[prefs[i] - 1];
        } else {
            str[i] = ++current_symbol;
        }
    }
    return str;
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

void test(const std::string str) {
    std::cout << "Input str: " << str << '\n';
    std::cout << "Input pref func: ";

    std::vector<int> pi = prefix_f(str);
    for (int val : pi) {
        std::cout << val << " ";
    }
    std::cout << '\n';

    std::string constructed = get_string_by_prefix(pi);
    std::vector<int> computed_pi = prefix_f(constructed);

    std::cout << "Result string: " << constructed << '\n';

    std::cout << "Pref func: ";
    for (int val : computed_pi) {
        std::cout << val << " ";
    }
    std::cout << '\n';

    bool correct = (pi == computed_pi);
    std::cout << "Is correct? " << (correct ? "yes" : "no") << '\n';
    std::cout << '\n';
}

int main() {
    test("ababaca");
    test("abcdef");
    test("aabaabaa");
    test("aaaaa");
    test("ahaolegahaolegaha");

    return 0;
}