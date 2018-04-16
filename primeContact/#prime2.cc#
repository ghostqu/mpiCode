#include<iostream>
#include<thread>
#include<cmath>
#include<vector>
using namespace std;

const uint64_t L1D_CACHE_SIZE = 32768;

class Prime {
private:
  // first sieve of prime
  char* seive;
  // size of the first sieve, should be sqrt(high)
  uint32_t seiveSize;
  // the total number of primes
  uint32_t count[2] = {0};
  // the range 
  uint64_t start, end;
  // the fist 144 primes
  bool* primeCheck;
  
  uint64_t findMinIndex2(uint64_t p, uint64_t s) {
    s = p * p > s ? p * p : s;
    uint64_t n = (s + p - 1) / p;
    int digit = n % 10;
    
    switch(p % 10) {
    case 1:
      n += ((digit <= 7) ? 7 - digit : 17 - digit);
      break;
    case 3:
      n += ((digit <= 9) ? 9 - digit : 19 - digit);
      break;
    case 7:
      n += ((digit <= 1) ? 1 - digit : 11 - digit);
      break;
    case 9:
      n += ((digit <= 3) ? 3 - digit : 13 - digit);
    }
    return n * p;
  }
  
  bool findLowerBoundary(uint64_t& index) {
    if(index < 100000) return false;
    //cout << index << endl;
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
    index = (prefix + 1) * zeros + 7;
    return true;
  }
  
  bool findDigitPrime(uint64_t n) {
    uint32_t x = 0;
    while(n != 0) {
      uint32_t digit = n % 10;
      n /= 10;
      if(digit == 2) return false;
      x += digit;
    }
    return primeCheck[x];
  }
public:
  Prime(uint64_t start, uint64_t end): start(start), end(end) {
    
    // count = 0;
    
    seiveSize = (uint32_t)(sqrt(end)) + 1;
    //cout << "size " << seiveSize << endl;;
    seive = new char[seiveSize];
    // 0 and 1 are not prime
    seive[0] = seive[1] = 0;
    // make all elements true
    for(int i = 2; i < seiveSize; i++) {
      *(seive + i) = 1;
    }
    // get first 145 primes
    primeCheck = new bool[145];
    for(int i = 0; i < 145; i++) primeCheck[i] = false;
    int a[] = {7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139};
    for(auto i : a) primeCheck[i] = true;
  }
  void seiveThread() {
    // size is for first loglogN size for thread
    const uint64_t size = (uint32_t)(sqrt(seiveSize)) + 1;
    //get first loglogN array for thread
    for(uint32_t i = 3; i <= size; i+=2) {
      if(*(seive + i)) {
        int next = i << 1;
        for(int j = i * i; j <= size; j += next) {
          *(seive + j) = 0;
        }
      }
    }
    // use two threads
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
    seive[5] = 0;
    findLowerBoundary(start);
    uint64_t rangeStart = start;
    uint64_t rangeMid = start + (end - start)/2;
    uint64_t rangeEnd = end;
    thread t[2];
    t[0] = thread(&Prime::threadSecond, this, rangeStart, rangeMid, 0);
    t[1] = thread(&Prime::threadSecond, this, rangeMid + 1, rangeEnd, 1);
    t[0].join();
    t[1].join();
    cout << "The amount of primes is " << count[0] + count[1] << endl;
  }
  void threadSecond(uint64_t s, uint64_t e, int x) {
    uint64_t segmentSize = seiveSize < L1D_CACHE_SIZE? seiveSize : L1D_CACHE_SIZE;
    vector<char> sieve(segmentSize);
    vector<int64_t> primes;
    vector<int64_t> indexes;
    findLowerBoundary(s);
    uint64_t low = s;
    low += low % 10 < 7? 7 - low % 10 : 17 - low % 10;
    uint64_t n = low;

    for(uint64_t i = 3; i < seiveSize; i += 2) {
      if(*(seive + i)) {
	primes.push_back(i);
	indexes.push_back(findMinIndex2(i, low) - low);
      }
    }
    
    for( ; low <= e; ) {
      fill(sieve.begin(), sieve.end(), true);
      uint64_t high = min(low + segmentSize - 1, e);
      for (uint32_t i = 0; i < primes.size(); i++)
	{
	  uint64_t j = indexes[i];
	  for (int64_t k = (primes[i] * 10); j < segmentSize; j += k)
	    sieve[j] = false;
	  indexes[i] = j - segmentSize;
	}
      for (; n <= high; n += 10) 
       	if (sieve[n - low] && findDigitPrime(n)) // n is a prime
	  //	  if(x == 0) cout << n << " ";
	  count[x]++;
      if(findLowerBoundary(low)) {
	for(uint32_t i = 0; i < primes.size(); i++) {
	  indexes[i] = findMinIndex2(primes[i], low) - low;
	}
	n = low;
      } else {
	low += segmentSize;
      }
      
    }
    //if(x == 0) cout << count[x] << endl;
  }
  void seiveThreadSingle(uint64_t p, uint32_t t) {
    //used last prime to avoid conflict
    uint64_t next = p * t;
    for(uint64_t i = p * p; i <= seiveSize; i += next) {
      *(seive + i) = 0;
    }
  }
  ~Prime() {
    delete[] seive;
    delete[] primeCheck;
    //delete[] count;
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
  start = atol(arg[1]);
  end = atol(arg[2]);
  Prime p(start, end);
  p.seiveThread();
  return 0;
}

