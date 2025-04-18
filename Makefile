main.exe: main.o calculator.o
	g++ -std=c++17 -o main.exe main.o calculator.o

main.o: main.cpp calculator.hpp
	g++ -std=c++17 -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	g++ -std=c++17 -c calculator.cpp

clean: 
	rm -f main.exe main.o calculator.o