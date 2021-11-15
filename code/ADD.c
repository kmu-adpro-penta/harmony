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

Output : C ( C > 0 ) +---------------------------******9

A 의 길이 = n
B 의 길이 = m  ( n > m )

*/
void ADDC(bigint* A, bigint* B, bigint** C) {
	
	bi_new(C, A->wordlen + 1);

	word c = 0;					// c : carry
	for (int j = 0; j < A->wordlen; j++) {
		if(j == B->wordlen)
			c = ADD_ABc(*(A->a + j), 0, c, (*C)->a + j);
		else
			c = ADD_ABc(*(A->a + j), *(B->a + j), c, (*C)->a+j);
	}

	*((*C)->a + A->wordlen) = c;

	if (c == 1) {
		(*C)->wordlen = A->wordlen + 1;
		(*C)->sign = NON_NEGATIVE;
	}
	else {
		(*C)->wordlen = A->wordlen;
		(*C)->sign = NON_NEGATIVE;
	}

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
 void bigint_ADD(bigint* A, bigint* B, bigint **C) {

	// if A = 0  then return B
	if (A->wordlen == 0)
		bi_assign(C,B);

	// if B = 0	 then return A
	if (B->wordlen == 0)
		bi_assign(C,A);

	// if A > 0  and  B < 0  then return A - |B|
	if (A->sign > 0 && B->sign < 0) {
		B->sign = NON_NEGATIVE;
		SUBC(&A, &B, C);
	}

	// if A < 0  and  B > 0  then return B - |A|
	if (A->sign < 0 && B->sign > 0) {
		A->sign = NON_NEGATIVE;
		SUBC(&B, &A, C);
	}

	// if A >= B then 
	if (A->wordlen >= B->wordlen)
		ADDC(A, B,C);  // return A + B
	// else (A < B)
	else
		ADDC(B, A,C);	// return B + A
}


