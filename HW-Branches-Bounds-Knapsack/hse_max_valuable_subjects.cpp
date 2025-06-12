#include <iostream>
#include <vector>
#include <string>
#include <utility>


std::pair<size_t, std::vector<std::string>> selectSubjects(size_t maxCredits, std::vector<size_t>& usefulness, std::vector<size_t>& credits, std::vector<std::string>& courseNames) {
    size_t n = usefulness.size();
    std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(maxCredits + 1, 0));

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 0; j <= maxCredits; j++) {
            dp[i][j] = dp[i-1][j];

            if (j >= credits[i-1]) {
                dp[i][j] = std::max(dp[i][j], dp[i-1][j - credits[i-1]] + usefulness[i-1]);
            }
        }
    }

    std::vector<std::string> selectedSubjects;
    size_t j = maxCredits;
    for (size_t i = n; i > 0; --i) {
        if (dp[i][j] != dp[i-1][j]) {
            selectedSubjects.push_back(courseNames[i-1]);
            j -= credits[i-1];
        }
    }

    return {dp[n][maxCredits], selectedSubjects};
}

int main() {
    size_t maxCredits = 1500;
    std::vector<size_t> usefulness = {40, 50, 100, 95, 30};
    std::vector<size_t> credits = {200, 314, 198, 500, 300};
    std::vector<std::string> courseNames = {
        "1", "2", "3", "4", "5"
    };

    auto start = std::chrono::steady_clock::now();
    auto [maxUsefulness, selectedSubjects] = selectSubjects(maxCredits, usefulness, credits, courseNames);
    auto diff = std::chrono::steady_clock::now() - start;
    std::cout << "Отработал за: " << std::chrono::duration<double, std::milli>(diff).count() << " мс\n";

    std::cout << "Максимальная полезность: " << maxUsefulness << "\n\n";
    std::cout << "Выбранные предметы:\n";
    for (auto& subject : selectedSubjects) {
        std::cout << subject << '\n';
    }

    return 0;
}