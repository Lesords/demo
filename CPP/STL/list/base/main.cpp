#include <iostream>
#include <stdio.h>
#include <list>

void debug(const std::string &debugInfo, std::list<int> &value) {
    printf("%s", debugInfo.c_str());
    for (auto v: value) printf("%d ", v);
    printf("\n");
}

int main() {
    std::list<int> listValue = {1, 2, 3, 4, 5};

    debug("origin: ", listValue);
    printf("size: %ld, front: %d, back: %d\n", listValue.size(), listValue.front(), listValue.back());

    for (auto v: listValue) v = 3;
    debug("after modify 3: ", listValue); // not work

    for (auto &v: listValue) v = 6;
    debug("after modify 6: ", listValue);

    void *pVoid = &listValue;
    for (auto &v: *(std::list<int> *) pVoid) v = 9;
    debug("after modify 9: ", listValue);

    listValue.clear();
    debug("after clear: ", listValue);

    for (int i = 1; i <= 5; ++i) listValue.push_back(i);
    debug("after push_back: ", listValue);

	return 0;
}
