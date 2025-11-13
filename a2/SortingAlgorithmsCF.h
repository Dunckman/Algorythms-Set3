#ifndef SET_2_SORTINGALGORITHMSCF_H
#define SET_2_SORTINGALGORITHMSCF_H

#include <vector>

inline void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

inline void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);
    for (int i = 0; i < n1; ++i) {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        right_arr[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        }
        else {
            arr[k++] = right_arr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = left_arr[i++];
    }
    while (j < n2) {
        arr[k++] = right_arr[j++];
    }
}

inline void standardMergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    standardMergeSort(arr, left, mid);
    standardMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

inline void hybridMergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    if (right - left + 1 <= 15) {
        insertionSort(arr, left, right);
    }
    else {
        int mid = left + (right - left) / 2;
        hybridMergeSort(arr, left, mid);
        hybridMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

#endif //SET_2_SORTINGALGORITHMSCF_H