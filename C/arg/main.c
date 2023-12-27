#include <stdio.h>
#include <stdlib.h> // atoi

// int main(int argc, char** argv) {
int main(int argc, char* argv[]) {
    int i;
    printf("argc: %d, values: ", argc);
	for (i = 0; i < argc; ++i) {
        // printf("%s, %d ", argv[i], atoi(argv[i]));
        printf("%s ", *(argv + i));
	}
	return 0;
}
