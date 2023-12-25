#include <iostream>
using namespace std;

#ifdef LIB_ERROR
void show(int a);
#endif

void debug(int a) {

#ifdef LIB_ERROR
    show(a);
#endif

	cout << "debug_val: " << a << "\n";
}
