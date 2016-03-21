testsecondpass : testsecondpass.o secondpass.o firstpass.o chario.o scanner.o tokentable.o token.o symboltable.o tools.o
	gcc -o testsecondpass testsecondpass.o secondpass.o firstpass.o scanner.o chario.o tokentable.o token.o symboltable.o tools.o

testsecondpass.o : testsecondpass.c secondpass.h firstpass.h chario.h symboltable.h tools.h
	gcc -c testsecondpass.c

secondpass.o : secondpass.c firstpass.h secondpass.h chario.h token.h scanner.h symboltable.h
	gcc -c secondpass.c

firstpass.o : firstpass.c firstpass.h chario.h token.h scanner.h symboltable.h
	gcc -c firstpass.c

scanner.o : scanner.c scanner.h chario.h token.h
	gcc -c scanner.c

chario.o : chario.c chario.h
	gcc -c chario.c

tokentable.o : tokentable.c tokentable.h token.h
	gcc -c tokentable.c

token.o : token.c token.h
	gcc -c token.c

symboltable.o : symboltable.c symboltable.h
	gcc -c symboltable.c

tools.o : tools.c tools.h
	gcc -c tools.c




