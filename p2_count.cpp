#include <iostream>
#include <vector>
 
void countSort(std::vector<int>& arr, int n) {
    std::vector<int> temp(2000001);
    for (int i = 0; i < n; i++) {
        ++temp[arr[i] + 1000000];
    }
    size_t ind = 0;
    for (int i = 0; i < 2000001; i++) {
        if (temp[i] != 0) {
            for (int j = 0; j < temp[i]; j++) {
                arr[ind++] = i - 1000000;
            }
        }
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
 
    countSort(nums, n);
    for (int i = 0; i < n; i++) {
        std::cout << nums[i] << " ";
    }
}