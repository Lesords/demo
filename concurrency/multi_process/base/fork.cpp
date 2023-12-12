#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
int main() {
	cout << "this is before fork position\n\n";
    int pid = fork();
	cout << "this is between fork and if position\n";
	if ( pid < 0 ) {
		cout << "fork failed\n";
	} else if ( pid == 0 ) {
		cout << "this is child process\n";
	} else {
		cout << "this is father process\n";
	}
	cout << "this is after fork operation\n\n";
	return 0;
}
