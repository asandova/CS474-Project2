all: PipeProgram SharedMemProgram MatrixProgram

PipeProgram: Pipe/Pipes.cpp
	g++ Pipe/Pipes.cpp -o PipeProgram

SharedMemProgram: SharedMem.o
	g++ SharedMem.o -o SharedMemoryProgram

SharedMem.o: SharedMemory/SharedMem.cpp
	g++ -c SharedMemory/SharedMem.cpp

MatrixProgram: Matrix.o MatrixDriver.o
	g++ Matrix.o MatrixDriver.o -pthread -o MatrixProgram

MatrixDriver.o: Matrix/Matrix.hpp
	g++ -c MatrixDriver.cpp

Matrix.o: Matrix/Matrix.cpp Matrix/Matrix.hpp
	g++ -c Matrix/Matrix.cpp

clean:
	rm -rf *.o
	if [ -f MatrixProgram ]; then rm MatrixProgram; fi;
	if [ -f PipeProgram ]; then rm PipeProgram; fi;
	if [ -f SharedMemoryProgram ]; then rm SharedMemoryProgram; fi;