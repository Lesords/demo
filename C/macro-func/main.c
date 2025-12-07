#include <stdio.h>

#define add(a, b) #a #b
#define func(a)   #a" is a function"

int main() {
    printf("%s\n", add(1, 2));
    printf("%s\n", add(hello, world));
    printf("%s\n", func(1));
    printf("%s\n", func("test"));
    return 0;
}
/*
 * output:
 * 12
 * helloworld
 * 1 is a function
 * "test" is a function
 */
