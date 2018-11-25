all: PipeProgram SharedMemProgram MatrixProgram

PipeProgram: Pipe/Pipes.cpp
	g++ Pipe/Pipes.cpp -o PipeProgram
SharedMemProgram:

MatrixProgram: Matrix.o MatrixDriver.o
	g++ Matrix.o MatrixDriver.o -pthread -o MatrixProgram

MatrixDriver.o: Matrix/Matrix.hpp
	g++ -c MatrixDriver.cpp

Matrix.o: Matrix/Matrix.cpp Matrix/Matrix.hpp
	g++ -c Matrix/Matrix.cpp

clean:
	rm -rf *.o
	if [ -f MatrixProgram ]; then rm MatrixProgram; fi;
	if [ -f Pipe ]; then rm Pipe; fi;