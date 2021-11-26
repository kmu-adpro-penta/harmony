#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
//#include "DIV.h"
#define MAIN

int main() {
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
	return 0;
}