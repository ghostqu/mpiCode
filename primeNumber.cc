#include<mpi.h>
#include<stdio.h>
#include<cmath>
#include<iostream>

using namespace std;
bool check(uint64_t);
int main(int argc, char** argv) {
  //cout << argv[1] << endl;
  int totalNum = 10000;
  MPI_Init(nullptr, nullptr);

  int worldSize;
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

  int worldRank;
  MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);

  char processorName[MPI_MAX_PROCESSOR_NAME];
  int nameLen;
  MPI_Get_processor_name(processorName, &nameLen);

  int res = 0;
  for(int id = 0; id < worldSize; id++) {
    if(worldRank == id) {
      int startNum = worldRank * totalNum / worldSize + 1;
      int endNum =  (worldRank + 1) * totalNum / worldSize;
      for(int i = startNum; i <= endNum; i++) {
	if(check(i)) res++;
      }
    }
  }

  cout << processorName << " rank "
       << worldRank << " result "
       << res << " worldSize " << worldSize << endl; 
  MPI_Finalize();
}

bool check(uint64_t num) {
  if(num < 1) return false;
  if(num == 2) return true;
  for(int i = 2; i < num; i++) {
    if(num % i == 0) return false;
  }
   return true;
}
