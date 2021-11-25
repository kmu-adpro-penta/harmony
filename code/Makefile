
bigint : main.o bigint.o sub.o add.o mul.o
	gcc -o bigint main.o bigint.o sub.o add.o mul.o

add.o :
	gcc -c -o add.o ADD.c

sub.o :
	gcc -c -o sub.o SUB.c

div.o :
	gcc -c -o div.o DIV.c

mul.o :
	gcc -c -o mul.o MUL.c

bigint.o : bigint.c
	gcc -c -o bigint.o bigint.c

main.o : main.c
	gcc -c -o main.o main.c

clear :
	rm *.o bigint