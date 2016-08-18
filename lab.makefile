CC    = g++
#CC   = clang++-3.6 -L /usr/lib/gcc/x86_64-linux-gnu/4.8 -I /usr/include/x86_64-linux-gnu/c++/4.8 -I /usr/include/c++/4.8

CXXFLAGS = -std=c++11 -g -Wall -pedantic


%.obj: %.cpp %.hpp
	$(CC) $(CXXFLAGS) $*.cpp -c -o $*.obj

%.out: %.cpp
	$(CC) $(CXXFLAGS) $*.cpp -o $*.out

game: clean GameLoop.out
	mv GameLoop.out rabies-rabbits

play: game
	clear
	@./rabies-rabbits 2>log.txt

valgrind: game
	clear
	@valgrind --tool=memcheck --leak-check=full ./rabies-rabbits 2>log.txt

clean:
	touch rabies-rabbits
	rm rabies-rabbits
	rm -f *.obj *.out
