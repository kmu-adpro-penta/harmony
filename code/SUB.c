#include "SUB.h"

void SUBAbB(word* A, word* B, word* C, word* b) {
	//A - input borrow
	*C = *A - *b;
	/*
	* A = 0, b = 1즉 A < b일 경우 next borrow = 1
	* C < B인 경우 underflow가 일어났으니 next borrow = 1
	* 둘 중 한 가지만 일어날 수 있으니 or연산
	*/
	word borrow = ((*A < *b) | (*C < *B));
	//C = A - b - B
	*C -= *B;
	//next borrow를 *b에 input
	*b = borrow;
}

void SUBC(bigint* A, bigint* B, bigint** C) {

	int i = 0;
	//B가 A보다 작은 경우 B대신 넣어줄 0
	word x = 0;
	//초기 borrow = 0
	word b = 0;
	//뺄셈 연산
	for (i; i < B->wordlen; i++)
		SUBAbB(&A->a[i], &B->a[i], &(*C)->a[i], &b);
	for (i; i < A->wordlen; i++)
		SUBAbB(&A->a[i], &x, &(*C)->a[i], &b);

}

void SUB(bigint* A, bigint* B, bigint** C) {
	//C가 NULL인 경우 C할당
	if(*C == NULL)
		bi_new(C, MAX(A->wordlen, B->wordlen));
	//부호가 같은 경우
	if (A->sign == B->sign) {
		//A >= B
		if (bi_compare_abs(A, B) + 1) SUBC(A, B, C);
		// A < B
		else {
			SUBC(B, A, C);
			(*C)->sign = NEGATIVE;
		}
	}
	//부호가 다른 경우
	else {
		//A가 양수
		if (!(A->sign)) {
			B->sign = NON_NEGATIVE;
			ADD(A, B, C);
		}
		//B가 양수
		else {
			A->sign = NON_NEGATIVE;
			ADD(A, B, C);
			(*C)->sign = NEGATIVE;
		}
	}
	bi_refine(*C);
}