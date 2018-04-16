#include<iostream>
#include<thread>
int main() {
  int* a = new int[1000000];
  for(int i = 0; i < 1000000; i++) a[i] = 0;
}
