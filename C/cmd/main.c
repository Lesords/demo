#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char value[128];

    fp = popen("ls", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(value, sizeof(value) - 1, fp) != NULL) {
        printf("%s", value);
    }

    pclose(fp);

    return 0;
}
