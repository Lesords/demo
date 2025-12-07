#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mut;
int num = 0;

void print(int id) {
    while (true) {
        std::lock_guard<std::mutex> lock(mut);
        if (num > 20) {
            printf("%d is over here\n", id);
            break;
        }
        printf("%d: %d\n", id, num++);
    }
}

int main() {
    std::vector<std::thread> vec;

    for (int i = 1; i <= 3; i++) {
        vec.emplace_back(std::thread(print, i));
    }

    for (int i = 0; i < 3; i++) {
        vec[i].join();
    }

    return 0;
}
