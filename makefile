usemylib : usemylib.o mylib.o
	gcc -o usemylib usemylib.o mylib.o

usemylib.o : usemylib.c mylib.h
	gcc -c usemylib.c

mylib.o : mylib.c mylib.h
	gcc -c mylib.c
