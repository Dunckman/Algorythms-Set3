#include <iostream>
#include <vector>
#include <random>
#include <cmath>
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
    const int N = 250000;

    std::vector<Circle> circles(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

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

    if (narrow_xmin >= narrow_xmax || narrow_ymin >= narrow_ymax) {
        std::cout << 0.0;
        return 0;
    }

    double area = calculateMonteCarloArea(N, narrow_xmin, narrow_xmax, narrow_ymin, narrow_ymax, circles);

    std::cout << area;
}