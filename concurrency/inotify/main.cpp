#include <stdio.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE      (sizeof (struct inotify_event))
#define EVENT_BUF_LEN   (1024 * (EVENT_SIZE + 16))

int main() {
    char buffer[EVENT_BUF_LEN];
    int fd, wd;

    fd = inotify_init();
    if (fd == -1) {
        perror("inotify_init");
        return -1;
    }

    wd = inotify_add_watch(fd, "/tmp", IN_CREATE | IN_DELETE | IN_OPEN | IN_ACCESS | IN_MODIFY | IN_ATTRIB);
    if (wd == -1) {
        perror("inotify_add_watch");
        return -1;
    }

    while(1) {
        int length = read(fd, buffer, EVENT_BUF_LEN);
        if (length < 0) {
            perror("read");
        }

        for (int i = 0; i < length; ) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if (event->len) {
                if (event->mask & IN_CREATE) {
                    printf("The file %s was created.\n", event->name);
                } else if (event->mask & IN_DELETE) {
                    printf("The file %s was deleted.\n", event->name);
                } else if (event->mask & IN_ACCESS) {
                    printf("The file %s was accessed.\n", event->name);
                } else if (event->mask & IN_OPEN) {
                    printf("The file %s was opened.\n", event->name);
                } else if (event->mask & IN_MODIFY) {
                    printf("The file %s was modified.\n", event->name);
                } else if (event->mask & IN_ATTRIB) {
                    printf("The file %s metadata changed.\n", event->name);
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}
