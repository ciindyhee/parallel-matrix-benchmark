CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
OPENMP_FLAGS = -fopenmp
TARGET = matrix_benchmark
SRC = src/main.cpp

all:
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) $(SRC) -o $(TARGET)

no-openmp:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
