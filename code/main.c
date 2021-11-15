#include "bigint.h"
#include <ADD.h>

#define MAIN
int main(){

	/*
	
	bigint* bi=NULL;
	bi_new(&bi, 2);
	word w[2] = {0x5678, 0x1234};

	printf("start\n");
	//bi_set_by_array(&bi, NON_NEGATIVE, w, 2);
	bi_set_by_string(&bi, NON_NEGATIVE, "1324812481adfe134124", 20);
	bi_lshift(&bi, 28);
	printf("worlen : %d\n", bi_get_wordlen(bi));
	bi_show_hex(bi);
	printf("\n");
	bi_realloc(&bi, 3);
	printf("worlen : %d\n", bi_get_wordlen(bi));
	bi_show_hex(bi);
	printf("\n");
	bi_delete(&bi);

	*/

	bigint* A = NULL;
	bi_new(&A, 2);
	word w[2] = { 0x5678, 0x1234 };
	bi_set_by_array(&A, NON_NEGATIVE, w, 2);

	bigint* B = NULL;
	bi_new(&B, 3);
	word w_2[3] = { 0x5678, 0x1237,0x0001 };
	bi_set_by_array(&B, NON_NEGATIVE, w_2, 3);

	bigint* C = NULL;

	bigint_ADD(A, B, &C);

	bi_show_hex(C);


	return 0;
}