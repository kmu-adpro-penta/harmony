#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
//#include "DIV.h"
#define MAIN


/*
void toy1() {
	bigint* A = NULL;
	bigint* B = NULL;

	word A_array[3] = { 0x1234,0x2345,0x3456 };
	word B_array[2] = { 0x3122,0x1234 };

	bi_set_by_array(&A, NON_NEGATIVE, A_array, 3);
	bi_set_by_array(&B, NON_NEGATIVE, B_array, 2);


	bigint* Q = NULL;
	bigint* R = NULL;


	printf("A = \n");
	bi_show_hex(A);
	printf("\nB = \n");
	bi_show_hex(B);

	DIV(&A, &B, &Q, &R);

	printf("\nQ = \n");
	bi_show_hex(Q);
	printf("\nR = \n");
	bi_show_hex(R);
}*/

int main(){
	bigint* A = NULL;
	bi_gen_rand(&A, NON_NEGATIVE, 4);

	bigint* B = NULL;
	bi_gen_rand(&B, NON_NEGATIVE, 6);

	bigint* C = NULL;
	bi_show_hex(A);
	printf("\n");
	bi_show_hex(B);
	printf("\n");
	MULC(A, B, &C);
	bi_refine(C);
	bi_show_hex(C);

		//bi_show_hex(C);
		//printf("\n");

		//bi_show_hex(C);

		//bigint* AA = NULL;
		//ADD(B, C, &AA);

		//bi_show_hex(AA);
		//printf("\n");

		//if (bi_compare(A, AA) != 0) {

		//	//bi_realloc(&A, 4);
		//	bi_show_hex(A);
		//	printf("\n");
		//	bi_show_hex(B);
		//	printf("\n");
		//	bi_show_hex(C);
		//	printf("\n");
		//	bi_show_hex(AA);
		//	printf("you die%d", i);
		//	return 0;
		//}
	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);

	printf("end\n");
	return 0;
}
