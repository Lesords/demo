#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void deleteFolderContent(const char *folderPath) {
    DIR *dir;
    struct dirent *ent;
    char fullpath[256];

    dir = opendir(folderPath);
    if (dir == NULL) {
        return;
    }

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s/%s", folderPath, ent->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                deleteFolderContent(fullpath);
                rmdir(fullpath);
            } else {
                unlink(fullpath);
            }
        }
    }

    closedir(dir);
}

int main() {
    const char* folderPath = "./tmp";

    deleteFolderContent(folderPath);
    printf("Directory '%s' cleared.\n", folderPath);

    return 0;
}
