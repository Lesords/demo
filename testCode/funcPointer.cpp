// 函数指针的应用
#include<iostream>
#include <stdio.h>
#include<string>
#include <vector>
#include <map>
using namespace std;
int get_val(int a, int b) {
  cout << "this is get_val function\n";
  cout << "a: " << a << ", b:" << b << "\n";
  cout << "val: " << a+b << "\n";
}    
int get_data(int a, int b) {
  cout << "this is get_data function\n";
  cout << "a: " << a << ", b:" << b << "\n";
  cout << "val: " << a*b << "\n";
}
void show(int a, int b, int (*get_v)(int,int)) {
  get_v(a, b);
}
int main() {
  show(1, 2, get_val); 
  show(3, 5, get_data);

  cout << "new test\n";
  int (*get_hh) (int, int);
  get_hh = get_data;
  get_hh(1, 2);
  return 0;
}
