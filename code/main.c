#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
//#include "DIV.h"
#define MAIN
int main(){
	
	for(int i=0; i<100000; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 31);
		//bi_show_hex(A);
		//printf("\n");

		//bi_new(&A, 23);
		//word w[2] = { 0x5678, 0x1237 };
		//bi_set_by_array(&A, NON_NEGATIVE, w, 2);
		//bi_set_by_string(&A, NON_NEGATIVE, "e2a1851a03e0c28d8be31cbcb06862b0a92e66c93c6d25598796337c114b6b3c12a0d6e40191daa35ec5a663c084", 92);

		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 25);
		//bi_show_hex(B);
		//printf("\n");

		//bi_new(&B, 20);
		//word w_2[3] = { 0x5678, 0x1234, 0x1234 }; 
		//bi_set_by_string(&B, NON_NEGATIVE, "1c3dd01e222eef766b7a0220298c4b58d8b515544c285f64f93ac74e83dab8ea874dd6fcaa2ca850", 80);
		//bi_set_by_array(&B, NON_NEGATIVE, w_2, 3);

		bigint* C = NULL;
		//bi_new(&C, MAX(A->wordlen, B->wordlen) + 1);

		//bi_show_hex(A);
		//printf("\n");
		//bi_show_hex(B);
		//printf("\n");

		SUB(&A, &B, &C);

		bi_refine(C);

		//bi_show_hex(C);
		//printf("\n");

		//bi_show_hex(C);

		bigint *AA = NULL;
		//bi_new(&AA, MAX(A->wordlen, B->wordlen) + 1);
		bigint_ADD(B, C, &AA);

		//bi_show_hex(AA);
		//printf("\n");

		if(bi_compare(A, AA) != 0) {
			
			//bi_realloc(&A, 4);
			bi_show_hex(A);
			printf("\n");
			bi_show_hex(B);
			printf("\n");
			bi_show_hex(C);
			printf("\n");
			bi_show_hex(AA);
			printf("you die%d", i); 
			return 0;
		}
	}

	printf("ok");
	return 0;
}