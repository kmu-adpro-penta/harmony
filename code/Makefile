
bigint : main.o bigint.o sub.o add.o
	gcc -o bigint main.o bigint.o sub.o add.o

add.o :
	gcc -c -o add.o ADD.c

sub.o :
	gcc -c -o sub.o SUB.c

bigint.o : bigint.c
	gcc -c -o bigint.o bigint.c

main.o : main.c
	gcc -c -o main.o main.c

clear :
	rm *.o bigint