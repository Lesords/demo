#include <iostream>
#include <unistd.h>
#include <thread>

using namespace std;

void add(int a, int b) {
    cout << "Result: " << a + b << "\n";
}

void modify_value(int &a) {
    for (int i = 0; i < 10; ++i) {
        a = !a;
        sleep(2);
    }
    a = -1;
}

void wait(int &a) {
    while (1) {
        if (a == -1) break;
        if (a) {
            cout << "a is true\n";
        } else {
            cout << "a is false\n";
        }
        sleep(1);
    }
}

int main() {
    thread th_a(add, 1, 2);
    th_a.detach();

    int value = 1;

    thread th_b(modify_value, std::ref(value));
    th_b.detach();

    thread th_c(wait, std::ref(value));
    th_c.join();

    cout << "end of thread\n";
    return 0;
}
