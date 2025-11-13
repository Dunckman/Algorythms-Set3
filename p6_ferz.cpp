#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

std::vector<int> solve_n_queens(int n) {
    const int max_attempts = 10;
    const int max_iter = 500000;
    const double start_temperature = 100.0;
    const double cooling_rate = 0.99;

    for (int attempt = 0; attempt < max_attempts; attempt++) {
        int seed = n * 1000 + attempt;
        std::mt19937 gen(seed);
        std::uniform_int_distribution int_dist(0, n-1);
        std::uniform_real_distribution real_dist(0.0, 1.0);

        std::vector<int> queens(n);
        std::vector rows(n, 0);
        std::vector diag1(2 * n - 1, 0);
        std::vector diag2(2 * n - 1, 0);

        for (int i = 0; i < n; i++) {
            queens[i] = int_dist(gen);
            rows[queens[i]]++;
            diag1[i + queens[i]]++;
            diag2[i - queens[i] + n - 1]++;
        }

        int total_conflicts = 0;
        for (int i = 0; i < n; i++) {
            total_conflicts += (rows[queens[i]] - 1) + (diag1[i + queens[i]] - 1) + (diag2[i - queens[i] + n - 1] - 1);
        }
        total_conflicts /= 2;

        double T = start_temperature;

        for (int iter = 0; iter < max_iter; iter++) {
            if (total_conflicts == 0) {
                return queens;
            }

            int i = int_dist(gen);
            int old_row = queens[i];
            int new_row;
            do {
                new_row = int_dist(gen);
            } while (new_row == old_row);

            int old_conflicts_i = (rows[old_row] - 1) + (diag1[i + old_row] - 1) + (diag2[i - old_row + n - 1] - 1);

            rows[old_row]--;
            diag1[i + old_row]--;
            diag2[i - old_row + n - 1]--;

            rows[new_row]++;
            diag1[i + new_row]++;
            diag2[i - new_row + n - 1]++;

            int new_conflicts_i = (rows[new_row] - 1) + (diag1[i + new_row] - 1) + (diag2[i - new_row + n - 1] - 1);

            int delta = new_conflicts_i - old_conflicts_i;

            if (delta < 0 || exp(-delta / T) > real_dist(gen)) {
                queens[i] = new_row;
                total_conflicts += delta;
            } else {
                rows[new_row]--;
                diag1[i + new_row]--;
                diag2[i - new_row + n - 1]--;

                rows[old_row]++;
                diag1[i + old_row]++;
                diag2[i - old_row + n - 1]++;
            }

            T *= cooling_rate;
        }
    }

    return std::vector(n, 0);
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> queens = solve_n_queens(n);
    for (int i = 0; i < n; i++) {
        std::cout << queens[i] + 1;
        if (i < n - 1) {
            std::cout << " ";
        }
    }
}