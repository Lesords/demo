#include <stdio.h>
#include <stdarg.h>

void func(int count, ...) {
    va_list args;

    va_start(args, count);

    for (int i = 0; i < count; i++) {
        printf("value: %f\n", va_arg(args, double));
    }

    va_end(args);
}

int main() {
    func(3, 1.1, 2.2, 3.3);
    return 0;
}
