testnumbers : testnumbers.o numbers.o
	gcc -o testnumbers testnumbers.o numbers.o

testnumbers.o : testnumbers.c numbers.h
	gcc -c testnumbers.c

numbers.o : numbers.c
	gcc -c numbers.c
