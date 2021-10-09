#include "bigint.h"
#include "ADD.h"
#include <stdio.h>
#include <stdlib.h>







//Algorithm 5 ADD_ABc(A,B,c)
word* ADD_ABc(word A, word B,word c) {
	word c_2 = 0;
	word C = A + B;
	if (C < A) {
		c_2 = 1;
	}
	C = C + c;
	if (C < c) {
		c_2 += 1;
	}
	
	word array_return[2] = {c_2,C};
	return array_return;
}

//Algorithm 6 ADDC(A,B)
bigint* ADDC(bigint* A, bigint* B) {

	//line 1
	word* array = (word*)malloc(sizeof(word) * A->wordlen);
	memcpy(array, B->a, sizeof(word) * B->wordlen);
	
	for (word i = B->wordlen; i < A->wordlen; i++) {
		array[i] = 0;
	}

	B->a = array;

	//line2
	word c = 0;
	word* C_array = (word*)malloc(sizeof(word) * A->wordlen);
	for (word j = 0; j < A->wordlen; j++) {
		word* return_ADD_ABc = ADD_ABc(*(A->a + j), *(B->a + j), c);
		c = return_ADD_ABc[0];
		C_array[j] = return_ADD_ABc[1];
	}

	//line 7 
	C_array[A->wordlen] = c;

	//line 8
	//B->wordlen = A->wordlen;

	if (c == 1) {
		bigint* C = NULL;
		bi_new(&C, A->wordlen+1);
		bi_set_by_array(&C, NON_NEGATIVE, C_array, A->wordlen+1);

		//bi_delete(&A);
		//bi_delete(&B);

		return C;
	}
	else {
		bigint* C = NULL;
		bi_new(&C, A->wordlen);
		bi_set_by_array(&C, NON_NEGATIVE, C_array, A->wordlen);

		//bi_delete(&A);
		//bi_delete(&B);

		return C;
	}

}

bigint* SUB(bigint* A, bigint* B) {

}

bigint* bigint_ADD(bigint* A, bigint* B) {
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


