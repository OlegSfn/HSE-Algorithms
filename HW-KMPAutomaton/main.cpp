#include <iostream>
#include <vector>
#include <string>
#include <set>

class KMPStringMatcher {
private:
    std::string pattern_;
    std::vector<std::vector<int>> automaton_;

    void buildAutomaton() {
        int m = pattern_.length();
        automaton_.resize(m + 1, std::vector<int>(256, 0));

        int suffix_link = 0;
        for (int state = 0; state <= m; ++state) {
            for (int c = 0; c < 256; c++) {
                automaton_[state][c] = automaton_[suffix_link][c];
            }

            if (state < m) {
                automaton_[state][pattern_[state]] = state + 1;
            }

            if (state > 0) {
                suffix_link = automaton_[suffix_link][pattern_[state-1]];
            }
        }
    }

public:
    KMPStringMatcher(const std::string& pattern) : pattern_(pattern) {
        buildAutomaton();
    }

    void printAutomaton(std::string& text) {
        std::set<char> unique_chars(pattern_.begin(), pattern_.end());
        for (char c : text) {
            unique_chars.insert(c);
        }

        std::cout << "States\t| ";
        for (char c : unique_chars) {
            std::cout << c << " | ";
        }

        std::cout << '\n' << std::string(9 + 4*unique_chars.size(), '-') << std::endl;

        for (int state = 0; state <= pattern_.length(); state++) {
            std::cout << "  " << state << "\t\t| ";

            for (char c : unique_chars) {
                std::cout << automaton_[state][c] << " | ";
            }

            std::cout << '\n';
        }
    }

    std::vector<int> search(const std::string& text) {
        std::vector<int> matches;
        int n = text.length();
        int m = pattern_.length();

        int state = 0;
        for (int i = 0; i < n; i++) {
            state = automaton_[state][text[i]];

            if (state == m) {
                matches.push_back(i - m + 1);
            }
        }

        return matches;
    }
};

int main() {
    std::string pattern = "HSEHSAB";
    std::string text = "HEHSEHSE";

    KMPStringMatcher matcher(pattern);
    matcher.printAutomaton(text);

    std::vector<int> matches = matcher.search(text);

    std::cout << "\npattern found at positions: ";
    for (int pos : matches) {
        std::cout << pos << " ";
    }

    return 0;
}