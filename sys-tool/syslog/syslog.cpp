#include <iostream>
#include <syslog.h>

int main() {
    openlog("syslog", LOG_CONS | LOG_PID, 0);

    setlogmask(LOG_UPTO(LOG_ERR));

    syslog(LOG_EMERG, "[EMERG] - 0 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_ALERT, "[ALERT] - 1 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_CRIT,  "[CRIT] - 2 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_ERR,   "[ERROR] - 3 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_WARNING, "[WARN] - 4 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_NOTICE, "[NOTICE] - 5 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_INFO,   "[INFO] - 6 - This is syslog test message[%d]\n", __LINE__);
    syslog(LOG_DEBUG,  "[DEBUG] - 7 -This is syslog test message[%d]\n", __LINE__);

    closelog();
    return 0;
}
