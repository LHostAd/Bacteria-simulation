all: main

main: main.o Bacteria.o Petri.o
	g++ main.o Bacteria.o Petri.o -o main
	
main.o : main.cpp Bacteria.h Petri.h 
	g++ -c main.cpp -o main.o -Wall -Wextra -std=c++11
  
Bacteria.o : Bacteria.h Bacteria.cpp
	g++ -c -g Bacteria.cpp -o Bacteria.o -std=c++11 -Wall -Wextra
	
Petri.o : Petri.h Petri.cpp
	g++ -c -g Petri.cpp -o Petri.o -std=c++11 -Wall -Wextra
	

clean:
	rm -f *.o 

