#include <iostream>
#include <thread>

using namespace std;

void test() {
    cout << "This is test function\n";
}

void wait() {
    while (1) {
    }
}

int main() {
    thread th_a(test);
    thread th_b(wait);

    th_a.detach();
    th_b.join();
    cout << "end of thread\n";
    return 0;
}
