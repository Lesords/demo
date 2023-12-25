#include <stdio.h>
#include <iostream>
#include <dlfcn.h>

int main() {
    void *dlhandler = NULL;
    void (*debug)(int a);

    dlhandler = dlopen("./libFunc.so", RTLD_LAZY);
    if (dlhandler == NULL) {
        fprintf(stderr, "load file error: %s\n", dlerror());
        return 1;
    }
    printf("Successfully load libFunc.so file\n");

    debug = (void(*) (int)) dlsym(dlhandler, "debug");
    if (dlerror() != NULL) {
        fprintf(stderr, "fun load error: %s\n", dlerror());
        return 1;
    }

    for (int i = 0; i <= 6; ++i) {
        debug(i);
    }

    dlclose(dlhandler);
    return 0;
}
