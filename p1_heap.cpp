#include <iostream>
#include <vector>

// без параметра размера нормально реализовать не получилось(
void heapify(std::vector<int>& arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != root) {
        std::swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    heapSort(nums);
    for (int i = 0; i < n; i++) {
        std::cout << nums[i] << " ";
    }
}