#include <sys/stat.h>
#include <stdio.h>

int main() {
    const char *dirName = "exampleDir";
    struct stat dirStat;

    // 判断目录是否存在
    if (stat(dirName, &dirStat) == 0) {
        // 如果stat调用成功，说明目录存在
        printf("目录 '%s' 存在\n", dirName);
    } else {
        // 如果stat调用失败，说明目录不存在或发生错误
        perror("目录不存在或发生错误");
    }

    return 0;
}
