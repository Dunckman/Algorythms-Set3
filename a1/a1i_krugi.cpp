#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
#include <algorithm>

struct Circle {
    double x = 0;
    double y = 0;
    double r = 0;
};

bool isPointInCircle(double px, double py, const Circle& c) {
    double dx = px - c.x;
    double dy = py - c.y;
    return dx * dx + dy * dy <= c.r * c.r;
}

double calculateMonteCarloArea(int N, double x_min, double x_max,
            double y_min, double y_max, const std::vector<Circle>& circles) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(x_min, x_max);
    std::uniform_real_distribution<> dis_y(y_min, y_max);

    int count_inside = 0;
    for (int i = 0; i < N; ++i) {
        double x = dis_x(gen);
        double y = dis_y(gen);

        bool in_all_circles = true;
        for (const auto& circle : circles) {
            if (!isPointInCircle(x, y, circle)) {
                in_all_circles = false;
                break;
            }
        }
        if (in_all_circles) {
            count_inside++;
        }
    }

    double area_rect = (x_max - x_min) * (y_max - y_min);
    return static_cast<double>(count_inside) / N * area_rect;
}

int main() {
    const std::vector<Circle> circles = {
        {1.0, 1.0, 1.0},
        {1.5, 2.0, std::sqrt(5.0) / 2.0},
        {2.0, 1.5, std::sqrt(5.0) / 2.0}
    };

    const double exact_area = 0.25 * std::numbers::pi + 1.25 * std::asin(0.8) - 1.0;

    const double wide_xmin = 0.0;
    const double wide_xmax = 3.118;
    const double wide_ymin = 0.0;
    const double wide_ymax = 3.118;

    const double narrow_xmin = std::max({circles[0].x - circles[0].r,
                                         circles[1].x - circles[1].r,
                                         circles[2].x - circles[2].r});
    const double narrow_xmax = std::min({circles[0].x + circles[0].r,
                                         circles[1].x + circles[1].r,
                                         circles[2].x + circles[2].r});
    const double narrow_ymin = std::max({circles[0].y - circles[0].r,
                                         circles[1].y - circles[1].r,
                                         circles[2].y - circles[2].r});
    const double narrow_ymax = std::min({circles[0].y + circles[0].r,
                                         circles[1].y + circles[1].r,
                                         circles[2].y + circles[2].r});


    std::ofstream outfile("../a1/monte_carlo_comparison_data.csv");
    outfile << "N;wide_area;narrow_area;wide_rel_error;narrow_rel_error;exact_area\n";

    for (int N = 100; N <= 100000; N += 500) {
        double estimated_area_wide = calculateMonteCarloArea(N, wide_xmin, wide_xmax, wide_ymin, wide_ymax, circles);
        double rel_error_wide = (std::abs(estimated_area_wide - exact_area) / exact_area) * 100.0;

        double estimated_area_narrow = calculateMonteCarloArea(N, narrow_xmin, narrow_xmax, narrow_ymin, narrow_ymax, circles);
        double rel_error_narrow = (std::abs(estimated_area_narrow - exact_area) / exact_area) * 100.0;

        outfile << N << ";"
                << estimated_area_wide << ";"
                << estimated_area_narrow << ";"
                << rel_error_wide << ";"
                << rel_error_narrow << ";"
                << exact_area << "\n";
    }
    double estimated_area_wide = calculateMonteCarloArea(100000, wide_xmin, wide_xmax, wide_ymin, wide_ymax, circles);
    double rel_error_wide = (std::abs(estimated_area_wide - exact_area) / exact_area) * 100.0;

    double estimated_area_narrow = calculateMonteCarloArea(100000, narrow_xmin, narrow_xmax, narrow_ymin, narrow_ymax, circles);
    double rel_error_narrow = (std::abs(estimated_area_narrow - exact_area) / exact_area) * 100.0;

    outfile << 100000 << ";"
            << estimated_area_wide << ";"
            << estimated_area_narrow << ";"
            << rel_error_wide << ";"
            << rel_error_narrow << ";"
            << exact_area << "\n";

    outfile.close();
    std::cout << "Data saved in file saved as \"monte_carlo_comparison_data.csv\"\n";
}