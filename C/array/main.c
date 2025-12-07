#include <stdio.h>

int main() {
    int a[] = {
        [0] 1,
        [1] = 1,
        [3] 1,
    };

    int i;
    for (i = 0; i <= 3; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
