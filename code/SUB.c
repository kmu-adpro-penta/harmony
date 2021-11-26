#include "SUB.h"

void SUBAbB(word* A, word* B, word* C, word* b) {
	//A�� input borrow�� �� ���� C�� �ִ´�
	*C = *A - *b;
	/*
	* C�� borrow���� ���� ���� A = 0, b = 1�� ���� �� �� next borrow = 1
	* C�� B���� ���� ��� ������ �ϸ� next borrow = 1
	* �� �� �� ��츸 �Ͼ��, borrow�� 0 or 1�̹Ƿ� �� ��츦 or���� ���־ ����
	*/
	word borrow = ((*A < *b) | (*C < *B));
	//���������� A - b - B���� C�� ����
	*C -= *B;
	//next borrow�� ���� input borrow���� �־��ش�
	*b = borrow;
}

void SUBC(bigint* A, bigint* B, bigint** C) {//��ȣ ���忭 �� �ٸ��� ����

	int i = 0;
	//A�� ���̰� B���� ��� A���� - B���� ������ ���� 0�� �־�� �ϹǷ� ����
	word x = 0;
	//�ʱ� borrow�� 0���� ����
	word b = 0;
	//�� �ڸ����� ����
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