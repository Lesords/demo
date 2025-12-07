#include <iostream>
#include <vector>
#include <initializer_list>

class A {
public:
    A(std::initializer_list<int> args) {
        for (const auto &value: args) {
            m_vec.push_back(value);
        }
    }

    void debug() {
        for (const auto &value: m_vec) {
            std::cout << value << " ";
        }
    }

private:
    std::vector<int> m_vec;
};

int main() {
    A a{1, 2, 3, 4};

    a.debug();
    return 0;
}
