main.o: main.cpp
	g++ -c main.cpp -o main.o

processor.o: processor.cpp
	g++ -c processor.cpp -o processor.o

instructions.o: instruction.cpp
	g++ -c instruction.cpp -o instruction.o

execute.o: execute.cpp
	g++ -c execute.cpp -o execute.o

processor8085.exe: main.o processor.o instruction.o execute.o
	g++ main.o processor.o instruction.o execute.o -o processor8085.exe


all: 
	make main.o
	make processor.o
	make instruction.o
	make execute.o
	make processor8085.exe
	
clean:
	rm -f *.o processor8085.exe