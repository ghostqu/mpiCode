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

  void taskManager() {
    
    
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
