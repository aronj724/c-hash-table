CC=gcc
CCFLAGS=-std=c11 -Wall -g3 -c
OBJS = hash_table.o main.o
PROGRAM = program

$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $^ -lm

hash_table.o : hash_table.h hash_table.c
	$(CC) $(CCFLAGS) hash_table.c

main.o : main.c hash_table.h
	$(CC) $(CCFLAGS) main.c

clean :
	rm -f *.o $(PROGRAM)