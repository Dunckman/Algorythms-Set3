#include <iostream>
#include <vector>
#include <string>

bool compareFractions(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first * b.second < b.first * a.second;
}

void merge(std::vector<std::pair<int, int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::pair<int, int>> leftArr(n1);
    std::vector<std::pair<int, int>> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (!compareFractions(rightArr[j], leftArr[i])) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<std::pair<int, int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::pair<int, int>> fractions(n);

    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        size_t pos = s.find('/');
        int numerator = std::stoi(s.substr(0, pos));
        int denominator = std::stoi(s.substr(pos + 1));
        fractions[i] = {numerator, denominator};
    }

    mergeSort(fractions, 0, n - 1);
    for (int i = 0; i < n; i++) {
        std::cout << fractions[i].first << '/' << fractions[i].second << " ";
    }
}