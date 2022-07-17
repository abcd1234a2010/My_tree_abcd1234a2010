%.o: %.c
	gcc -g -c $^

all: My_random.o Tree.o
	gcc -g main.c My_random.o Tree.o

debug1: My_random.o Tree.o
	gcc -g -DDEBUG1 main.c My_random.o Tree.o

debug2: My_random.o Tree.o
	gcc -g -DDEBUG2 main.c My_random.o Tree.o

debug3: My_random.o Tree.o
	gcc -g -DDEBUG3 main.c My_random.o Tree.o

clean:
	rm *.o *.so *.a