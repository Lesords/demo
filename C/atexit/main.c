#include <stdio.h>
#include <stdlib.h>

void test() { // must be void
    printf("[atexit] this is %s function\n", __func__);
}

int main() {
	atexit(test);
    printf("main function end here\n");

	// exit(0); // call atexit function too
	return 0;
}
