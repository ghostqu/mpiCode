#include<mpi.h>
#include<stdio.h>
#include<cmath>
#include<iostream>

using namespace std;
class WorldManager {
private:
  int worldSize;
  int worldRank;
  char processorName[MPI_MAX_PROCESSOR_NAME];
  int nameLen;
public:
  WorldManager() {
    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
    MPI_Get_processor_name(processorName, &nameLen);
  }
  int getSize() {
    return worldSize;
  }
  int getRank() {
    return worldRank;
  }
  string getName() {
    string s ="";
    for(int i = 0; i < nameLen; i++) {
      s += processorName[i];
    }
    return s;
  }
  void run() {
    int totalNum = 100;
    int* task = nullptr;
    int rangeNum = totalNum / worldSize;
    int curStart = 1;
    if(worldRank == 0) {
      task = (int*)malloc(sizeof(int)* worldSize);
      for(int i = 0; i < worldSize; i++) {
	task[i] = 1 + rangeNum * i;
      }
    }
    MPI_Scatter(task, 1, MPI_INT, &curStart, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int res = 0;
    for(int i = curStart; i < curStart + rangeNum; i++) {
      if(check(i)) {
	res++;
	//cout << i << endl;
      }
    }
    if(worldRank != 0) task = nullptr;
    MPI_Gather(&res, 1, MPI_INT, task, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(worldRank == 0) {
      res = 0;
      for(int i = 0; i < worldSize; i++) {
	res += task[i];
      }
      cout << "the result is " << res << endl;
    }
    
  }
  
  bool check(uint64_t num) {
    if(num <= 1) return false;
    //if(num == 2) return true;
    for(int i = 2; i <= sqrt(num); i++) {
      if(num % i == 0) return false;
    }
    return true;
  }
  ~WorldManager() {
    MPI_Finalize();
  }
};

int main(int argc, char** argv) {
  WorldManager wm;
  
  wm.run();
  
}
