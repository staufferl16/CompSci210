filestats : filestats.o
	gcc -o filestats filestats.o

filestats.o : filestats.c
	gcc -c filestats.c
