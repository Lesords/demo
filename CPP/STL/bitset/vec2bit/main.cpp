#include <iostream>
#include <vector>
#include <bitset>

void debug(const std::bitset<64> &value, int flag = 0) {
    std::cout << "bitset: ";
    for (int i = 0; i < 64; i++) {
        std::cout << value[i];
        if (flag && (i + 1) % 8 == 0) std::cout << " ";
    }
    std::cout << "\n";
}

void debug_value(const std::bitset<64> &value) {
    int nVal = 0, nCnt = 0;

    std::cout << "bitset(int): ";
    for(int i = 0; i < 64; i++) {
        nVal |= value[i] << nCnt;
        if(++nCnt == 8) {
            std::cout << nVal << " ";
            nCnt = nVal = 0;
        }
    }
    std::cout << "\n";
}

int main() {
    int nPos = 0;
    std::bitset<64> bsVal;
    std::vector<uint16_t> vecVal;

    for(int i = 0; i < 8; i++) vecVal.push_back(i);

    std::cout << "vector: ";
    for(auto v: vecVal) {
        std::cout << v << " ";
        for(int i = 0; i < 8; i++) {
            int cur = ((v >> i) & 1);
            bsVal[nPos++] = cur;
        }
    }
    std::cout << '\n';

    debug(bsVal, 1);
    debug_value(bsVal);

    return 0;
}
