#ifndef SET_2_SORTTESTER_H
#define SET_2_SORTTESTER_H

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include "ArrayGenerator.h"
#include "SortingAlgorithms.h"

class SortTester {
public:
    static long long testStandardMergeSort(std::vector<int>& arr) {
        auto start = std::chrono::high_resolution_clock::now();
        standardMergeSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }

    static long long testHybridMergeSort(std::vector<int>& arr, int threshold) {
        auto start = std::chrono::high_resolution_clock::now();
        hybridMergeSort(arr, 0, arr.size() - 1, threshold);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }

    static void runTests() {
        const int MAX_SIZE = 100000;
        const int STEP = 100;
        const int RUN_COUNT = 5;
        const std::vector thresholds = {5, 10, 20, 30, 50, 100};

        std::ofstream randomFile("../a2/files/results_random.csv");
        std::ofstream reversedFile("../a2/files/results_reversed.csv");
        std::ofstream almostSortedFile("../a2/files/results_almost_sorted.csv");

        std::vector<std::ofstream*> files = {&randomFile, &reversedFile, &almostSortedFile};

        std::string header = "ArraySize;StandardMergeSort";
        for (int t : thresholds) {
            header += ";HybridMergeSort" + std::to_string(t) + "";
        }
        for (auto file : files) {
            *file << header << "\n";
        }

        std::cout << "Generating master arrays...\n";
        auto masterRandom = ArrayGenerator::generateRandomArray(MAX_SIZE);
        auto masterReversed = ArrayGenerator::generateReversedArray(MAX_SIZE);
        auto masterAlmostSorted = ArrayGenerator::generateAlmostSortedArray(MAX_SIZE, MAX_SIZE / 100);
        std::vector<std::vector<int>> masterArrays = {masterRandom, masterReversed, masterAlmostSorted};

        for (int size = STEP; size <= MAX_SIZE; size += STEP) {
            for (int type = 0; type < 3; ++type) {
                std::ofstream& currentFile = *files[type];
                currentFile << size;

                long long totalTimeStandard = 0;
                for (int i = 0; i < RUN_COUNT; ++i) {
                    std::vector<int> tempArray(masterArrays[type].begin(), masterArrays[type].begin() + size);
                    totalTimeStandard += testStandardMergeSort(tempArray);
                }
                currentFile << ";" << totalTimeStandard / RUN_COUNT;

                for (int threshold : thresholds) {
                    long long totalTimeHybrid = 0;
                    for (int i = 0; i < RUN_COUNT; ++i) {
                        std::vector<int> tempArray(masterArrays[type].begin(), masterArrays[type].begin() + size);
                        totalTimeHybrid += testHybridMergeSort(tempArray, threshold);
                    }
                    currentFile << ";" << totalTimeHybrid / RUN_COUNT;
                }
                currentFile << "\n";
            }
        }

        for (auto file : files) {
            file->close();
        }

        std::cout << "Tests finished. Results are saved to:\n";
        std::cout << "- results_random.csv\n";
        std::cout << "- results_reversed.csv\n";
        std::cout << "- results_almost_sorted.csv\n";
    }
};

#endif //SET_2_SORTTESTER_H