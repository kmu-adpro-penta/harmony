
bigint : main.o bigint.o
	gcc -o bigint main.o bigint.o

bigint.o : bigint.c
	gcc -c -o bigint.o bigint.c

main.o : main.c
	gcc -c -o main.o main.c

clear :
	rm *.o bigint