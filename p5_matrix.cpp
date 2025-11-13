#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <random>
#include <string>

constexpr int MAX_N = 4000;

int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    }
    if (c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');
    }
    return 0;
}

std::bitset<MAX_N> hexBlockToBitset(const std::string& block, int n) {
    std::bitset<MAX_N> result;
    int bit_pos = 0;

    for (char hex_digit : block) {
        int value = hexCharToInt(hex_digit);
        for (int i = 3; i >= 0; i--) {
            if (bit_pos < n) {
                result[bit_pos] = (value >> i) & 1;
                bit_pos++;
            } else {
                break;
            }
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    std::cin.ignore();
    std::vector<std::bitset<MAX_N>> A(n), B(n), C(n);

    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss_A(line);
    for (int i = 0; i < n; i++) {
        std::string block;
        ss_A >> block;
        A[i] = hexBlockToBitset(block, n);
    }

    std::getline(std::cin, line);
    std::stringstream ss_B(line);
    for (int i = 0; i < n; i++) {
        std::string block;
        ss_B >> block;
        B[i] = hexBlockToBitset(block, n);
    }

    std::getline(std::cin, line);
    std::stringstream ss_C(line);
    for (int i = 0; i < n; i++) {
        std::string block;
        ss_C >> block;
        C[i] = hexBlockToBitset(block, n);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    bool flag = true;
    for (int i = 0; i < 10; i++) {
        std::bitset<MAX_N> x;
        for (int j = 0; j < n; j++) {
            x[j] = dis(gen);
        }

        std::bitset<MAX_N> Bx;
        for (int j = 0; j < n; j++) {
            Bx[j] = (B[j] & x).count() % 2;
        }

        std::bitset<MAX_N> ABx;
        for (int j = 0; j < n; j++) {
            ABx[j] = (A[j] & Bx).count() % 2;
        }

        std::bitset<MAX_N> Cx;
        for (int j = 0; j < n; j++) {
            Cx[j] = (C[j] & x).count() % 2;
        }

        if (ABx != Cx) {
            flag = false;
            break;
        }
    }

    std::cout << (flag ? "YES" : "NO");
}