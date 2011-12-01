
all:
	gcc -Wall -O2 -lpthread -lrt -o phil.out phil.c

clean:
	rm -f *.o
	rm -f *.out

