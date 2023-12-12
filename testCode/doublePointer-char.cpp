#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	char *s = (char *) "123456";
	cout << s << "\n";
	printf("%s\n", s);

	char **ss = &s;
	cout << ss << "\n";
	printf("%p\n", ss);
	printf("%p\n", *ss);

	for (int i = 0; i < (int)strlen(*ss); i++) {
		printf("%c\n", *((*ss) + i));
	}

	return 0;
}
