all: assignment2

assignment2: assignment2.c
	gcc -Wall -ggdb assignment2.c -o assignment2 -lm

clean:
		rm assignment2