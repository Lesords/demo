#include <iostream>

class A {
public:
    A();
    A(int nVal, double fVal): m_nVal(nVal), m_fVal(fVal) {}

    A& operator = (const A &a) {
        m_nVal = a.m_nVal;
        m_fVal = a.m_fVal;
        return *this;
    }

    operator int() {
        return m_nVal;
    }

    operator double() {
        return m_fVal;
    }

private:
    int m_nVal;
    double m_fVal;
};

int main() {
    A a(1, 1.2);
    A b(2, 2.3);

    std::cout << int(a) << " " << double(a) << "\n";

    a = b;
    std::cout << int(a) << " " << double(a) << "\n";

    return 0;
}
