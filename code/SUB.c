#include "SUB.h"

void SUBAbB(word* A, word* B, word* C, word* b) {
	//A에 input borrow를 뺀 값을 C에 넣는다
	*C = *A - *b;
	/*
	* C가 borrow보다 작은 경우는 A = 0, b = 1인 경우고 이 때 next borrow = 1
	* C가 B보다 작은 경우 뺄셈을 하면 next borrow = 1
	* 둘 중 한 경우만 일어나고, borrow는 0 or 1이므로 두 경우를 or연산 해주어도 무방
	*/
	word borrow = ((*C < *b) | (*C < *B));
	//최종적으로 A - b - B값이 C에 들어간다
	*C -= *B;
	//next borrow를 다음 input borrow값에 넣어준다
	*b = borrow;
}

void SUBC(bigint* A, bigint* B, bigint** C) {//부호 워드열 다 다르게 검증

	word i = 0;
	//A의 길이가 B보다 길면 A길이 - B길이 이후의 값에 0을 넣어야 하므로 만듦
	word x = 0;
	//초기 borrow를 0으로 설정
	word b = 0;
	//각 자릿수의 연산
	for (i; i < B->wordlen; i++)
		SUBAbB(&A->a[i], &B->a[i], &(*C)->a[i], &b);
	for (i; i < A->wordlen; i++)
		SUBAbB(&A->a[i], &x, &(*C)->a[i], &b);

}

void SUB(bigint* A, bigint* B, bigint** C) {//입력값 체크
	//부호가 같을 경우
	bi_new(C, MAX(A->wordlen, B->wordlen));
	if (A->sign == B->sign) {
		//printf("SUB\n");
		//A가 B보다 클 경우 결과는 +
		if (A->wordlen > B->wordlen) SUBC(A, B, C);
		
		else if (A->wordlen < B->wordlen) {
			SUBC(B, A, C);
			(*C)->sign = NEGATIVE;
		}
		//A보다 B가 클 경우 결과는 -
		else
			if (A->a[A->wordlen - 1] < B->a[B->wordlen - 1]) {
				SUBC(B, A, C);
				(*C)->sign = NEGATIVE;
			}
		//A가 B보다 클 경우 결과는 non_negative
		else SUBC(A, B, C);
	}
	//부호가 다를 경우
	else {
		//
		if (!(A->sign)) {
			B->sign = NON_NEGATIVE;
			bigint_ADD(A, B, C);
		}
		else {
			A->sign = NON_NEGATIVE;
			bigint_ADD(A, B, C);
			(*C)->sign = NEGATIVE;
		}
	}
}