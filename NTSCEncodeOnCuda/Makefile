
EXECUTABLE := testEncode

CU_FILES   := ntscProcess.cu

CU_DEPS    :=

CC_FILES   := main.cpp lodepng.cpp

###########################################################

ARCH=$(shell uname | sed -e 's/-.*//g')

OBJDIR=objs
CXX=g++ -m64
CXXFLAGS=-O3 -Wall
ifeq ($(ARCH), Darwin)
# Building on mac
LDFLAGS=-L/usr/local/cuda-8.0/lib/ -lcudart
#LDFLAGS=-L/usr/local/depot/cuda-7.5/lib/ -lcudart
else
# Building on Linux
LDFLAGS=-L/usr/local/cuda-8.0/lib64/ -lcudart
#LDFLAGS=-L/usr/local/depot/cuda-7.5/lib64/ -lcudart
endif
NVCC=nvcc
NVCCFLAGS=-O3 -m64


OBJS=$(OBJDIR)/main.o  $(OBJDIR)/lodepng.o  $(OBJDIR)/ntscProcess.o


.PHONY: dirs clean

default: $(EXECUTABLE)

dirs:
		mkdir -p $(OBJDIR)/

clean:
		rm -rf $(OBJDIR) *.ppm *~ $(EXECUTABLE)

$(EXECUTABLE): dirs $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
		$(CXX) $< $(CXXFLAGS) -c -o $@

$(OBJDIR)/%.o: %.cu
		$(NVCC) $< $(NVCCFLAGS) -c -o $@
