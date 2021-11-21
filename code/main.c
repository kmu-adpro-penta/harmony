#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
//#include "DIV.h"
#define MAIN
int main(){
	
	bigint* A = NULL;
	bi_new(&A, 2);
	word w[2] = { 0x5678, 0x1237 };
	bi_set_by_array(&A, NON_NEGATIVE, w, 2);

	bigint* B = NULL;
	bi_new(&B, 3);
	word w_2[3] = { 0x5678, 0x1234, 0x1234 }; 
	bi_set_by_array(&B, NON_NEGATIVE, w_2, 3);

	bigint* C = NULL;
	bi_new(&C, MAX(A->wordlen, B->wordlen) + 1);

	bi_show_hex(A);
	printf("\n");
	bi_show_hex(B);
	printf("\n");

	bigint_ADD(A, B, &C);
	bi_show_hex(C);



	return 0;
}