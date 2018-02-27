#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
  int* task = nullptr;
  int worldSize = 4;
  int rangeNum = 10;
  task = new int[worldSize * 2];
  for(int i = 0; i < worldSize; i++) {
    task[i * 2] =  rangeNum * i;
    task[i * 2 + 1] = rangeNum * (i + 1);
  }
  for(int i = 0 ; i < worldSize * 2; i++) cout << task[i] << " ";
}
