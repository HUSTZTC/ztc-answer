CXXFLAGS=-Og -g -fsanitize=address -Wall -Wextra -Wshadow  -pipe

all: main

main: baseline.o main.o solution.o
	g++ $(CXXFLAGS) -o $@ $^

baseline.o: baseline.cc
	g++ -O0 -g -Wall -Wextra -Wshadow -pipe -c -o $@ $^

main.0: main.cc
	g++ -O0 -Wall -Wextra -Wshadow -pipe -c -o $@ $^

solution.o: solution.cc
	g++ -O3 -Wall -Wextra -Wshadow -pipe -c -o $@ $^

clean:
	rm -f *.o main
