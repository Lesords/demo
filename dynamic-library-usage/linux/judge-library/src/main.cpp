#include <stdio.h>
#include <stdlib.h> // exit
#include <dlfcn.h>  // dlopen

#define LIB_PATH "./libdebug.so"

int main() {
    void *dlhandler;

    dlhandler = dlopen(LIB_PATH, RTLD_NOW);
    if (dlhandler == NULL) {
        fprintf(stderr, "%s\n", dlerror());
        exit(-1);
    }

    dlclose(dlhandler);
    printf("The library is normal\n");
    return 0;
}
