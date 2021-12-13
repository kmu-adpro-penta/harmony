#include "bigint.h"
#include "ADD.h"
#include "SUB.h"

/*

Input : A,B and c  ( 0 < A,B <= W and c = 0 or 1)

Ourput : C and c'  ( A + B + c = c'W +C )

*/

word ADD_ABc(word A, word B,word c,word* C_j) {
	word c_2 = 0;
	word C = A + B;
	if (C < A) {
		c_2 = 1;
	}
	C = C + c;
	if (C < c) {
		c_2 += 1;
	}
	*C_j = C;
	return c_2;
}

/*

Input : A , B  ( A,B > 0 and A > B )

Output : C ( C > 0 ) 

*/
void ADDC(bigint* A, bigint* B, bigint** C) {
	
	word c = 0;					// c : carry
	for (int j = 0; j < A->wordlen; j++) {
		if (j >= B->wordlen)
			c = ADD_ABc(*(A->a + j), 0, c, (*C)->a + j);
		else
			c = ADD_ABc(*(A->a + j), *(B->a + j), c, (*C)->a + j);
	}
	
	if (c == 1) {
		*((*C)->a + A->wordlen) = c;
		(*C)->wordlen = A->wordlen + 1;
	}
	else 
		(*C)->wordlen = A->wordlen;
}


/*

bigint_ADD

Input : A,B		Output : A + B

case 1. A = 0
case 2. B = 0 
case 3. A > 0 and B < 0
case 4. A < 0 and B > 0
case 5. A > B or A < B  ( A,B > 0 )


*/

void ADD(bigint* A, bigint* B, bigint **C) {
	int A_sign = A->sign;
	int B_sign = B->sign;

	// if A = 0  then return B
	if (A->wordlen == 0)
		bi_assign(C,B);

	// if B = 0	 then return A
	if (B->wordlen == 0)
		bi_assign(C,A);
	bigint* temp = NULL;
	bi_new(&temp, MAX(A->wordlen, B->wordlen) + 1);

	// if A > 0  and  B < 0  then return A - |B|
	if (A->sign == NON_NEGATIVE && B->sign == NEGATIVE) {
		B->sign = NON_NEGATIVE;
		SUB(A, B, &temp);
	}

	// if A < 0  and  B > 0  then return B - |A|
	else if (A->sign == NEGATIVE && B->sign == NON_NEGATIVE) {
		A->sign = NON_NEGATIVE;
		SUB(B, A, &temp);
	}

	// if A >= B then 
	else if (A->wordlen >= B->wordlen) {
		A->sign = NON_NEGATIVE;
		B->sign = NON_NEGATIVE;
		ADDC(A, B, &temp);  // return A + B
	// else (A < B)
	}
	else {
		A->sign = NON_NEGATIVE;
		B->sign = NON_NEGATIVE;
		ADDC(B, A, &temp);	// return B + A
	}

	if (A_sign == NEGATIVE && B_sign == NEGATIVE) {
		temp->sign = NEGATIVE;
	}

	bi_refine(temp);
	bi_assign(C, temp);
	bi_delete(&temp);
}


