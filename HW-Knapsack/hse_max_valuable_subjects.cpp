#include <iostream>
#include <vector>
#include <string>
#include <utility>


std::pair<size_t, std::vector<std::string>> selectSubjects(size_t maxCredits, std::vector<std::string>& subjectNames, std::vector<size_t>& usefulness, std::vector<size_t>& credits) {
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
            selectedSubjects.push_back(subjectNames[i-1]);
            j -= credits[i-1];
        }
    }

    return {dp[n][maxCredits], selectedSubjects};
}

int main() {
    size_t maxCredits = 15;
    std::vector<std::string> subjectNames = {
        "Матанализ", "Анализ данных", "Алгоритмы",
        "Диффуры", "Уравнения мат. физики", "Алгебра", "Маш. обучение"
    };
    std::vector<size_t> usefulness = {3, 3, 5, 2, 2, 4, 5};
    std::vector<size_t> credits = {3, 3, 4, 5, 3, 2, 3};

    auto [maxUsefulness, selectedSubjects] = selectSubjects(maxCredits, subjectNames, usefulness, credits);

    std::cout << "Максимальная полезность: " << maxUsefulness << "\n\n";
    std::cout << "Выбранные предметы:\n";
    for (auto& subject : selectedSubjects) {
        std::cout << subject << '\n';
    }

    return 0;
}