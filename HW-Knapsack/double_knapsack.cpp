#include <algorithm>
#include <iostream>
#include <vector>


size_t SolveMaxWeightVolumeKnapsack(size_t maxWeight, size_t maxVolume, std::vector<size_t>& values, std::vector<size_t>& weights, std::vector<size_t>& volumes) {
    size_t n = values.size();
    std::vector<std::vector<std::vector<size_t>>> dp(n + 1, std::vector<std::vector<size_t>>(maxWeight + 1, std::vector<size_t>(maxVolume + 1, 0)));

    for (size_t i = 1; i <= n; ++i) {
        for (size_t w1 = 0; w1 <= maxWeight; ++w1) {
            for (size_t w2 = 0; w2 <= maxVolume; ++w2) {
                dp[i][w1][w2] = dp[i-1][w1][w2];

                if (w1 >= weights[i - 1] && w2 >= volumes[i - 1]) {
                    dp[i][w1][w2] = std::max(dp[i][w1][w2], dp[i-1][w1 - weights[i-1]][w2 - volumes[i-1]] + values[i-1]);
                }
            }
        }
    }

    return dp[n][maxWeight][maxVolume];
}

int main() {
    size_t maxWeight = 5;
    size_t maxVolume = 6;

    std::vector<size_t> values = {8, 10, 15, 4};
    std::vector<size_t> weights = {2, 2, 3, 1};
    std::vector<size_t> volumes = {3, 1, 4, 2};

    size_t max_value = SolveMaxWeightVolumeKnapsack(maxWeight, maxVolume, values, weights, volumes);
    std::cout << "Максимальная стоимость: " << max_value << '\n';

    return 0;
}