all: a.out b.out c.out
a.out: prime2.cc
	g++ -std=c++11 -O2 -pthread prime2.cc -o a.out
b.out: prime3.cc
	g++ -std=c++11 -O2 prime3.cc -o b.out
c.out: prime4.cc
	g++ -std=c++11 -O2 -pthread prime4.cc -o c.out
