#include <stdio.h>
#include <string.h>

void test_strcat() {
    char str[20] = "hello ";

    strcat(str, "world!");

    printf("%s\n", str);
}

void test_strtok() {
    char str[] = "hello,world";
    char *token = strtok(str, ",");

    while(token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
}

int main() {
    test_strcat();

    test_strtok();
    return 0;
}
