#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#define MAIN

void toy1() {
	int i;
	for (i = 0; i < repeat; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 100);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 100);
		bigint* C = NULL;
		//printf("A = ");
		//bi_show_hex(A);
		//printf("\nB = ");
		//bi_show_hex(B);
		//printf("\nC = ");

		KaratsubaMUL(2, A, B, &C);
		//bi_show_hex(C);

		bi_delete(&A);
		bi_delete(&B);
		bi_delete(&C);
	}
}

void toy2() {
	for (int i = 0; i < 100; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 5);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 3);

		bigint* Q = NULL;
		bigint* R = NULL;

		printf("\n");
		printf("print(");
		bi_show_hex(A);
		printf(" // ");
		bi_show_hex(B);
		DIV(A, B, &Q, &R);
		printf(" == ");
		bi_show_hex(Q);
		printf(")");

		printf("\n");
		printf("print(");
		bi_show_hex(A);
		printf(" %% ");
		bi_show_hex(B);
		printf(" == ");
		bi_show_hex(R);
		printf(")");


	}

}

void toy3() {
	bigint* C = NULL;
	bigint* D = NULL;
	bigint** A = NULL;
	bi_gen_rand(&C, NON_NEGATIVE, 3);


	bi_assign(&D, C);
	bi_assign(A, C);


}


int main() {
	srand(time(NULL));
	clock_t start, end;
	start = clock();
	toy1();
	end = clock();
	printf("\nruntime is %fms",(double)(end - start) / repeat);
	return 0;
}