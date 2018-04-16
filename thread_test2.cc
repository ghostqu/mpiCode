#include<iostream>
#include<thread>
using namespace std;
void bar(int* a, int start, int end) {
   for(int i = start; i < end; i++) a[i] = 0;
}
int main() {
  int* a = new int[1000000];
  thread p1(bar, a, 0, 500000);
  thread p2(bar, a, 500000, 1000000);
  cout << "a " <<endl;
  return 0;
}

