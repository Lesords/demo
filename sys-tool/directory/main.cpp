#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    const char *dirName = "exampleDir";
    mode_t mode = 0755; // 设置目录权限

    // 创建目录
    if (mkdir(dirName, mode) == 0) {
        printf("目录创建成功\n");
    } else {
        perror("目录创建失败");
    }

    return 0;
}

