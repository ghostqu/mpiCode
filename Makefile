CXX	:= 	mpicxx
DEBUG	:=	-g
OPT	:=	-O2
OPTS	:=	-std=c++11
COMP	:= $(CXX) $(DEBUG) $(OPT) $(OPTS)
a.out:	mpi_mandelbrot.cc
	$(COMP)   ./mpi_mandelbrot.cc

asm:
	$(COMP)  -S ./mpi_mandelbrot.cc
clean:
	rm a.out
