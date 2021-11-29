#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#define MAIN

void toy1() {

	//int i = 0;
	//for (i; i < 10000; i++) {
	srand(time(NULL));
	bigint* A = NULL;
	bi_gen_rand(&A, NON_NEGATIVE, 3);
	bigint* B = NULL;
	bi_gen_rand(&B, NON_NEGATIVE, 3);
	bigint* C = NULL;
	printf("A = ");
	bi_show_hex(A);
	printf("\nB = ");
	bi_show_hex(B);
	printf("\n");

	KaratsubaMUL(2, A, B, &C);
	printf("C =");
	bi_show_hex(C);
	//printf("\nAA = ");

//bigint* AA = NULL;
//ADD(B, C, &AA);

//bi_show_hex(AA);
//printf("\n");

//if (bi_compare(A, AA) != 0) {

	//	//bi_realloc(&A, 4);
	//	printf("you die%d", i);
	//	printf("\n");
	//	return 0;
	//}
	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);
	//bi_delete(&AA);
//}
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

	toy2();
	return 0;
}