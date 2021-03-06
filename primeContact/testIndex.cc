#include<iostream>
#include<thread>
#include<cmath>
#include<vector>
using namespace std;

const uint64_t L1D_CACHE_SIZE = 32768;

class Prime {
private:
  char* seive;
  uint32_t seiveSize;
  uint32_t count;
  uint64_t start, end;
  // vector<uint64_t> prime;
  uint64_t findMinIndex(uint64_t index, uint64_t ss) {
    uint64_t n = index * index;
    uint64_t step;
    while(n < ss) {
      step = index << 1;
      while(n + step < ss) {
	n += step;
	step = step << 1;
      }
      n += (index << 1);
    }
    return n;
  }
  uint64_t findMinIndex2(uint64_t index, uint64_t ss) {
    uint64_t n = index * index;
    uint64_t step = ss / index;
    if(n < ss) { 
      n = step * index;
      if(n % 2 == 0) n += index;
      while(n < ss) n += 2 * index;
    }
    return n;
  }
public:
  Prime(uint64_t start, uint64_t end): start(start), end(end) {
    count = 0;
    seiveSize = (uint32_t)(sqrt(end)) + 1;
    //cout << "size " << seiveSize << endl;;
    seive = new char[seiveSize];
    //char* p = seive;
    seive[0] = seive[1] = 0;
    for(int i = 2; i < seiveSize; i++) {
      *(seive + i) = 1;
    }
  }
  void seiveThread() {
    // size is for first loglogN size for thread
    const uint64_t size = (uint32_t)(sqrt(seiveSize)) + 1;
    //get rid of all even numbers
    for(uint32_t i = 4; i <= seiveSize; i+=2) {
      *(seive + i) = 0;
    }
    //get first loglogN array for thread
    for(uint32_t i = 3; i <= size; i+=2) {
      if(*(seive + i)) {
        int next = i << 1;
        for(int j = i * i; j <= size; j += next) {
          *(seive + j) = 0;
        }
      }
    }
    thread v[2];
    for(uint32_t i = 3; i <= size;) {
      for(uint32_t j = 0; j < 2; j++, i+=2) {
	uint32_t times = 2;
        while(i <= seiveSize && *(seive + i) == 0) i += 2;
	v[j] = thread(&Prime::seiveThreadSingle, this, i, times);
	times = i;
      }
      v[0].join();
      v[1].join();     
    }
    
    uint64_t segmentSize = seiveSize < L1D_CACHE_SIZE? seiveSize : L1D_CACHE_SIZE;
    vector<char> sieve(segmentSize);
    vector<int64_t> primes;
    vector<int64_t> indexes;
    uint64_t low = start % 2 == 0? start + 1 : start;
    uint64_t n = low;
    
    for(uint64_t i = 3; i < seiveSize; i += 2) {
      if(*(seive + i)) {
	primes.push_back(i);
	indexes.push_back(findMinIndex(i, low) - low);
	uint64_t kk, bb;
	kk = findMinIndex(i,start);
	bb = findMinIndex2(i, start);
	cout << i << " the index is ";
	cout << kk  << endl;
	cout << "Another way's result " << bb << " TorF: " << (kk == bb)  << endl;
      }
    }

  }
  void seiveThreadSingle(uint64_t p, uint32_t t) {
    //used last prime to avoid conflict
    uint64_t next = p * t;
    for(uint64_t i = p * p; i <= seiveSize; i += next) {
      *(seive + i) = 0;
    }
  }
  void seiveSingle() {
    for(int i = 4; i <= seiveSize; i+=2) { // get rid of all even numbers
      *(seive + i) = 0;
    }
    for(int i = 3; i <= seiveSize; i+=2) { // just check the odd numbers
      if(*(seive + i)) {
        int next = i << 1; // this is i * 2
	for(int j = i * i; j <= seiveSize; j += next) {
          *(seive + j) = 0;
        }
      }
    }
  }
  int countP() {
    for(int i = 0; i < seiveSize; i++) {
      //cout << (int)(*(seive + i))  << " ";
      if(*(seive + i)) {
	//cout << i << " ";
	count++;
      }
      //return count;
    }
    return count;
  }
  ~Prime() {
    delete[] seive;
  }
};
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
      //cout << i << " ";

    }
  }
  cout << endl;
  delete[] arr;
  return count;
}
int main(int args, char** arg) {
  uint64_t start = 0;
  uint64_t end = 0;
  int test = 0;
  if(args == 2) {
    end = atol(arg[1]);
  } else if(args == 3) {
    start = atol(arg[1]);
    end = atol(arg[2]);
  } else {
    start = atol(arg[1]);
    end = atol(arg[2]);
    test = atoi(arg[3]);
    cout << "Not a correct input!" << endl;
  }
  if(test == 0) {
    Prime p(start, end);
    p.seiveThread();
    //cout << p.countP() << endl;
    //cout << count(end) << endl;
  } else {
    cout << count(end) <<endl;
  }
  return 0;
}

