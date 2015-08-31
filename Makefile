
CC=gcc

allfive: allfive.c pokerlib.o
	${CC} allfive.c pokerlib.o -s -o allfive

pokerlib.o: pokerlib.c arrays.h
	${CC} -c pokerlib.c -o pokerlib.o
clean:
	rm allfive pokerlib.o
test: echo OK
