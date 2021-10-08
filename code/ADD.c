#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>



using namespace std;


word ADD_mod_w(word A, word B) {
	return (A + B) >> ( sizeof(word)*8 );
}

word* ADD_ABc(word *A, word *B,word c) {
	word c_2 = 0;
	word C = ADD_mod_w(*A, *B);
	if (C < *A) {
		c_2 = 1;
	}
	C = ADD_mod_w(C,c);
	if (C < c) {
		c_2 += 1;
	}
	
	word array_return[2] = {c_2,C};
	return array_return;
}


bigint* ADDC(bigint* A, bigint* B) {

	for (word i = A->wordlen - B->wordlen; i < A->wordlen; i++) {
		*((B->a) + i) = 0;
	}

	word c = 0;
	bigint* C = NULL;
	bi_new(&C, A->wordlen);

	for (word j = 0; j < A->wordlen; j++) {
		return_array = ADD_ABc(A->a + j, B->a + j, c);
		c, *((C->a) + j) = return_array[0],return_array[1];
	}

	*(C->a + A->wordlen) = c;

	if (*(C->a + A->wordlen) == 1) {
		C->wordlen = A->wordlen;
		bi_delete(&A);
		bi_delete(&B);

		return C;
	}
	else {
		C->wordlen = A->wordlen - 1;

		bi_delete(&A);
		bi_delete(&B);
		return C;
	}

}

bigint* SUB(bigint* A, bigint* B) {

}

bigint* ADD(bigint* A, bigint* B) {
	if (A->wordlen == 0)
		return B;

	if (B->wordlen == 0)
		return A;

	if (A->sign > 0 && B->sign < 0) {
		B->sign = NON_NEGATIVE;
		return SUB(A, B);
	}

	if (A->sign < 0 && B->sign > 0) {
		A->sign = NON_NEGATIVE;
		return SUB(B, A);
	}

	if (A->wordlen >= B->wordlen)
		return ADDC(A, B);
	else
		return ADDC(B, A);
}


