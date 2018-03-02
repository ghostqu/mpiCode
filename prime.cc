#include<iostream>
using namespace std;
int count(uint64_t size) {
  int count = 0;
  char* arr = new char[size + 1];
  for(uint64_t i = 0; i <= size; i++) arr[i] = 0;
  arr[1] = 1;
  arr[0] = 1; //0, 1 are not prime number
  for(uint64_t i = 2; i < size + 1; i++) {
    if(arr[i] == 0) // if i is a prime
      for(uint64_t j = i * i; j < size + 1; j += i) {
	arr[j] = 1;
      }
  }
  for(uint64_t i = 0; i < size + 1; i++) {
    if(arr[i] == 0) {
      count++; // if arr[i] == 0 i is a prime
      cout << i << " ";

    }
  }
  cout << endl;
  delete[] arr;
  return count;
}
int main() {
  cout << count(100000000);
}
