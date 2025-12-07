#include <iostream>
#include <stdio.h>
#include <list>

struct node{
	int x,y;
	friend bool operator == (node a, node b) {
		if (a.x == b.x) return a.y == b.y;
		return a.x == b.x;
	}
};

void debug(const std::list<node> &value) {
    for (auto v: value) {
        printf("%d %d\n", v.x, v.y);
    }
    printf("\n");
}

void debug_point(const std::list<node> &value) {
	for (auto v = value.begin(); v != value.end(); ++v) {
        printf("%d %d\n", v->x, v->y);
	}
    printf("\n");
}

int main() {
	std::list<node> liVal;

	for (int i = 1; i <= 4; ++i) {
		liVal.push_back({i, 1});
	}

    debug(liVal);
    debug_point(liVal);

    // insert before
    liVal.insert(liVal.begin(), {1, 2});
    liVal.insert(liVal.end(), {4, 2});

    debug(liVal);

	return 0;
}
