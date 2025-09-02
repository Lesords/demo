#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char value[128] = "This is a sample string for tokenization";
    char *rest = value; // 存储剩余的字符串

    char *token = strtok_r(rest, " ", &rest);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok_r(NULL, " ", &rest);
    }

    return 0;
}
