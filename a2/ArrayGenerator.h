#ifndef SET_2_ARRAYGENERATOR_H
#define SET_2_ARRAYGENERATOR_H

#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>

class ArrayGenerator {
public:
    static std::vector<int> generateRandomArray(int size, int min_val = 0, int max_val = 6000) {
        if (size <= 0) {
            return {};
        }

        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min_val, max_val);

        for (int i = 0; i < size; ++i) {
            arr[i] = distrib(gen);
        }
        return arr;
    }

    static std::vector<int> generateReversedArray(int size, int min_val = 0, int max_val = 6000) {
        if (size <= 0) {
            return {};
        }

        std::vector<int> arr = generateRandomArray(size, min_val, max_val);
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        return arr;
    }

    static std::vector<int> generateAlmostSortedArray(int size, int swap_count) {
        if (size <= 0) {
            return {};
        }
        if (size < 2 && swap_count > 0) {
            throw std::invalid_argument("Size must be bigger than 2");
        }

        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = i;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);

        for (int i = 0; i < swap_count; ++i) {
            int idx1 = distrib(gen);
            int idx2 = distrib(gen);
            if (idx1 == idx2) {
                idx2 = (idx1 + 1) % size;
            }
            std::swap(arr[idx1], arr[idx2]);
        }
        return arr;
    }
};

#endif //SET_2_ARRAYGENERATOR_H