#include <iostream>
#include <vector>
#include <cstdint>
 
void radixSort(std::vector<int32_t>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return;
    }
 
    std::vector<uint32_t> transformed(n);
    std::vector<uint32_t> temp(n);
    for (int i = 0; i < n; i++) {
        transformed[i] = static_cast<uint32_t>(arr[i]) ^ (1U << 31);
    }
 
    std::vector<uint32_t>* a = &transformed;
    std::vector<uint32_t>* b = &temp;
    for (int byte = 0; byte < 4; byte++) {
        int count[256] = {0};
        for (int i = 0; i < n; i++) {
            uint32_t value = (*a)[i];
            uint32_t current_byte = (value >> (byte * 8)) & 0xFF;
            count[current_byte]++;
        }
 
        int total = 0;
        for (int i = 0; i < 256; i++) {
            int old_count = count[i];
            count[i] = total;
            total += old_count;
        }
 
        for (int i = 0; i < n; i++) {
            uint32_t value = (*a)[i];
            uint32_t current_byte = (value >> (byte * 8)) & 0xFF;
            (*b)[count[current_byte]] = value;
            count[current_byte]++;
        }
 
        std::swap(a, b);
    }
 
    for (int i = 0; i < n; i++) {
        arr[i] = static_cast<int32_t>((*a)[i] ^ (1U << 31));
    }
}
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int n = 0;
    std::cin >> n;
    std::vector<int32_t> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
 
    radixSort(nums);
    for (int i = 0; i < n; i++) {
        std::cout << nums[i] << " ";
    }
}