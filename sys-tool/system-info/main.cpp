#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

void getUsername() {
    char username[30];
    struct passwd *pw = getpwuid(getuid());

    if (pw) {
        strncpy(username, pw->pw_name, sizeof(username));
    } else {
        perror("getpwuid");
        return ;
    }

    printf("Username: %s\n", username);
}

void getHostname() {
    char hostname[30];

    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        return ;
    }

    printf("Hostname: %s\n", hostname);
}

int main() {
    getUsername();

    getHostname();
    return 0;
}
