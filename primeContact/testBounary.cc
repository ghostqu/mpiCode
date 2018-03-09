#include<iostream>
#include<cmath>

using namespace std;
bool findLowerBoundary(uint64_t& index) {
    if(index < 100000) return false;
cout << index << endl;
    uint64_t temp = index, prefix = 0;
    int a = 0, i = 0;
    while(temp > 0) {
      if(temp % 10 == 2) {
	prefix = temp;
	a = i;
      }
      temp /= 10;
      i++;
    }
    if(a < 5) return false;
    uint64_t zeros = (uint64_t)(pow(10, a));
cout << zeros << endl;
cout << a << endl;
    index = (prefix + 1) * zeros + 7;
    return true;
}
int main() {
  uint64_t t = 15314321321;
  if(findLowerBoundary(t))
    cout << t << endl;
}
