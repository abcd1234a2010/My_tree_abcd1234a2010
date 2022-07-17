%.o: %.c
	g++ -g -c $^

all: My_random.o Tree.o
	g++ -g main.cpp My_random.o Tree.o

debug1: My_random.o Tree.o
	g++ -g -DDEBUG1 main.cpp My_random.o Tree.o

debug2: My_random.o Tree.o
	g++ -g -DDEBUG2 main.cpp My_random.o Tree.o

clean:
	rm *.o *.so *.a