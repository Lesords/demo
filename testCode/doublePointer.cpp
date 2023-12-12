#include<iostream>
using namespace std;
void Init(int **a) {
  **a = 3;
}
int main() {
  int val = 2;
  int *a = &val;
  printf("val: %d\n", val);
  Init(&a);
  printf("val: %d\n", val);
  return 0;
}
