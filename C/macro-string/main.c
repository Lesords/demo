#include <stdio.h>

#define LOG(level) ("[" #level "] - macro string\n")
#define LOG_DEBUG LOG(DEBUG)
#define LOG_INFO  LOG(INFO)

int main() {

    printf(LOG_DEBUG);
    printf(LOG_INFO);

    return 0;
}
