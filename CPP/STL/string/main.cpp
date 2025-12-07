#include <iostream>
#include <string>

using namespace std;

int main() {
    string s = "a[123, 312]";

    printf("s.substr(2): %s\n", s.substr(2).c_str());

    std::string::size_type sz;
    int nValue = stoi(s.substr(2), &sz);
    printf("nValue: %d\n", nValue); // 123
    printf("sz: %lu\n", sz);        // 3

    printf("%d=%d\n", stoi(string(s, 2, 3)), stoi(string(s, 7, 3)));
    return 0;
}
