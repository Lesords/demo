#include <stdio.h>
#include <time.h>
#include <unistd.h>

void get_current_time() {
	struct tm *systime;
	time_t current_time;

	time(&current_time);
	systime = localtime(&current_time);

	printf("Year: %d\n", systime->tm_year + 1900);
	printf("Month: %d\n", systime->tm_mon + 1);
	printf("Day: %d\n", systime->tm_mday);
	printf("DayOfWeek: %d\n", systime->tm_wday);
	printf("Hour: %d\n", systime->tm_hour);
	printf("Minute: %d\n", systime->tm_min);
	printf("Second: %d\n", systime->tm_sec);
}

int main() {

    get_current_time();

	return 0;
}
