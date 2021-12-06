CC = gcc
CFLAGS = -Wall


bigint : main.o bigint.o sub.o add.o mul.o mod.o div.o
	$(CC) $(CFLAGS) -o bigint main.o bigint.o sub.o add.o mul.o mod.o div.o

test : test.o bigint.o sub.o add.o mul.o mod.o div.o
	$(CC) $(CFLAGS) -o test test.o bigint.o sub.o add.o mul.o mod.o div.o

add.o :
	$(CC) $(CFLAGS) -c -o add.o ADD.c

sub.o :
	$(CC) $(CFLAGS) -c -o sub.o SUB.c

div.o :
	$(CC) $(CFLAGS) -c -o div.o DIV.c

mul.o :
	$(CC) $(CFLAGS) -c -o mul.o MUL.c

mod.o :
	$(CC) $(CFLAGS) -c -o mod.o MOD.c

bigint.o : bigint.c
	$(CC) $(CFLAGS) -c -o bigint.o bigint.c

main.o : main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

test.o :
	$(CC) $(CFLAGS) -c -o test.o test.c

clean :
	rm *.o bigint
cleantest :
	del *.o test