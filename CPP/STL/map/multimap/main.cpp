#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

typedef pair<string, string> pss;

void debug(const multimap<int, int> &value) {
    printf("multimap value - size: %lu\n", value.size());
    for (auto v: value) {
        printf("%d = %d\n", v.first, v.second);
    }
    printf("\n");
}

void getValueOf(const multimap<int, int> &value, int index) {
    int cnt = value.count(index);
    auto it = value.find(index);

    printf("multimap find - size: %d\n", cnt);
    while (cnt--) {
        printf("%d = %d\n", it->first, it->second);
        it++;
    }
}

int main() {
    multimap<int, int> mp;
    mp.insert({1, 1});
    mp.insert({1, 2});
    mp.insert({2, 3});

    debug(mp);
    getValueOf(mp, 1);

    return 0;
}
