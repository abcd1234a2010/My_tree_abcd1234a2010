%.o: %.c
	g++ -std=c++17 -g -c $^

all: My_random.o Tree.o
	g++ -std=c++17 -g main.cpp My_random.o Tree.o

debug1: My_random.o Tree.o
	g++ -std=c++17 -g -DDEBUG1 main.cpp My_random.o Tree.o

debug2: My_random.o Tree.o
	g++ -std=c++17 -g -DDEBUG2 main.cpp My_random.o Tree.o

clean:
	rm *.o *.so *.a