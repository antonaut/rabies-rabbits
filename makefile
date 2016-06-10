#CC    = g++
CC   = clang++-3.6 -I /usr/include/x86_64-linux-gnu/c++/4.8 -I /usr/include/c++/4.8
LDFLAGS = -lm -L /usr/lib/gcc/x86_64-linux-gnu/4.8
CXXFLAGS = -std=c++11 -g -Wall -pedantic

%.obj: %.cpp
	$(CC) $(CXXFLAGS) $*.cpp -c -o $*.obj

%.out: %.cpp
	$(CC) $(CXXFLAGS) $*.cpp -o $*.out $(LDFLAGS)

test: clean test.out
	./test.out

game: clean GameLoop.out
	mv ./GameLoop.out ./rabiesrabbies

clean:
	rm -f *.obj *.out
	touch ./rabiesrabbits
	rm ./rabiesrabbits
