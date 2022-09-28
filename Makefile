Project4610: main.o sdisk.o block.o
	g++ -o Project4610 main.o sdisk.o block.o

main.o: main.cpp
	g++ -c main.cpp

sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp

block.o: block.cpp
	g++ -c block.cpp

filesys.o: filesys.cpp
	g++ -c filesys.cpp
	
clean:
	rm *.o Project4610
	rm test
	clear
