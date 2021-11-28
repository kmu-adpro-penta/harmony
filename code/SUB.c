#include "SUB.h"

void SUBAbB(word* A, word* B, word* C, word* b) {
	//A - input borrow
	*C = *A - *b;
	/*
	* A = 0, b = 1�� A < b�� ��� next borrow = 1
	* C < B�� ��� underflow�� �Ͼ���� next borrow = 1
	* �� �� �� ������ �Ͼ �� ������ or����
	*/
	word borrow = ((*A < *b) | (*C < *B));
	//C = A - b - B
	*C -= *B;
	//next borrow�� *b�� input
	*b = borrow;
}

void SUBC(bigint* A, bigint* B, bigint** C) {

	int i;
	//B�� A���� ���� ��� B��� �־��� 0
	word x = 0;
	//�ʱ� borrow = 0
	word b = 0;
	//���� ����
	for (i=0; i < B->wordlen; i++)
		SUBAbB(&A->a[i], &B->a[i], &(*C)->a[i], &b);
	for (i=B->wordlen; i < A->wordlen; i++)
		SUBAbB(&A->a[i], &x, &(*C)->a[i], &b);

}

void SUB(bigint* A, bigint* B, bigint** C) {
	//C�� NULL�� ��� C�Ҵ�
	if(*C == NULL)
		bi_new(C, MAX(A->wordlen, B->wordlen));
	//��ȣ�� ���� ���
	if (A->sign == B->sign) {
		//A >= B
		if (bi_compare_abs(A, B) + 1) SUBC(A, B, C);
		// A < B
		else {
			SUBC(B, A, C);
			(*C)->sign = NEGATIVE;
		}
	}
	//��ȣ�� �ٸ� ���
	else {
		//A�� ���
		if (!(A->sign)) {
			B->sign = NON_NEGATIVE;
			ADD(A, B, C);
		}
		//B�� ���
		else {
			A->sign = NON_NEGATIVE;
			ADD(A, B, C);
			(*C)->sign = NEGATIVE;
		}
	}
	bi_refine(*C);
}