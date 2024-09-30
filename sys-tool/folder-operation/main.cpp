#include <iostream>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#include <string.h>
#include <dirent.h>

#define FOLDER_CREATE 1
#define FOLDER_CLEAR  1

static int createFolder(const char* dirName) {
    struct stat dirStat;
    mode_t mode = 0755;

    if (stat(dirName, &dirStat) != 0) {
        if (mkdir(dirName, mode) != 0) {
            return -1;
        }
    }

    return 0;
}

static int clearCurrentFolder(const char* dirName) {
    DIR* dir;
    struct dirent* ent;
    char fullpath[128];

    dir = opendir(dirName);
    if (dir == NULL) {
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirName, ent->d_name);
        if (remove(fullpath) != 0) {
            return -1;
        }
    }

    closedir(dir);

    return 0;
}


int main() {
    std::string folder = "tmp";
    int ret = 0;

#if FOLDER_CREATE
    ret = createFolder(folder.c_str());
    if (ret == 0) {
        printf("%s create successful\n", folder.c_str());
    } else {
        printf("%s create failed\n", folder.c_str());
    }
#endif

#if FOLDER_CLEAR
    ret = clearCurrentFolder(folder.c_str());
    if (ret == 0) {
        printf("%s clear successful\n", folder.c_str());
    } else {
        printf("%s clear failed\n", folder.c_str());
    }
#endif

    return 0;
}
