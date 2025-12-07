#include <iostream>

class A {
public:
    A(): m_nVal(getValue()) {}
    explicit A(int nVal): m_nVal(nVal) {}

    int getValue() {
        return 10;
    }

    void debug() {
        std::cout << m_nVal << "\n";
    }

private:
    int m_nVal;
};

int main() {
    A a;
    a.debug();

    // a = {1}; // compile failed, because explicit
    a = A(1);   // compile pass
    a.debug();
    return 0;
}
