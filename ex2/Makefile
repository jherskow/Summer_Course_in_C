
CFLAGS = -g -Wextra -Wall -Wvla -std=c99

default: MyStringExample
	./MyStringExample

LineSeparator: LineSeparator.o
	gcc -g LineSeparator.o -o LineSeparator

LineSeparator.o: LineSeparator.c LineSeparator.h
	gcc $(CFLAGS) -c LineSeparator.c

MyStringExample: MyStringExample.o MyString.o
	gcc -g MyStringExample.o MyString.o -o MyStringExample

MyStringExample.o: MyStringExample.c MyString.h
	gcc -g $(CFLAGS) -c MyStringExample.c

MyString.o: MyString.c MyString.h
	gcc $(CFLAGS) -c MyString.c

clean:
	rm -f *.o *~ LineSeparator MyString MyStringExample