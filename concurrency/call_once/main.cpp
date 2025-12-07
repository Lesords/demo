#include <iostream>
#include <mutex>
#include <thread>

std::once_flag flag;

void call_func(int i) {
    printf("call_func - index: %d\n", i);
}

void test_func(int i) {
    std::call_once(flag, call_func, i);
}

int main() {
    std::thread t1(test_func, 1);
    std::thread t2(test_func, 2);
    std::thread t3(test_func, 3);

    t1.join();
    t2.join();
    t3.join();

    printf("all work done");

    return 0;
}
