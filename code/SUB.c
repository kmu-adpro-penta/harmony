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

	word i = 0;
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

void SUB(bigint* A, bigint* B, bigint** C) {//�Է°� üũ
	//��ȣ�� ���� ���
	bi_new(C, MAX(A->wordlen, B->wordlen));
	if (A->sign == B->sign) {
		//printf("SUB\n");
		//A�� B���� Ŭ ��� ����� +
		if (A->wordlen > B->wordlen) SUBC(A, B, C);
		
		else if (A->wordlen < B->wordlen) {
			SUBC(B, A, C);
			(*C)->sign = NEGATIVE;
		}
		//A���� B�� Ŭ ��� ����� -
		else
			if (A->a[A->wordlen - 1] < B->a[B->wordlen - 1]) {
				SUBC(B, A, C);
				(*C)->sign = NEGATIVE;
			}
		//A�� B���� Ŭ ��� ����� non_negative
		else SUBC(A, B, C);
	}
	//��ȣ�� �ٸ� ���
	else {
		//
		if (!(A->sign)) {
			B->sign = NON_NEGATIVE;
			ADD(A, B, C);
		}
		else {
			A->sign = NON_NEGATIVE;
			ADD(A, B, C);
			(*C)->sign = NEGATIVE;
		}
	}
	bi_refine(*C);
}