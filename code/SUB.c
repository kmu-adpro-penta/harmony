#include "SUB.h"

void SUBAbB(word* A, word* B, word* C, word* b) {
	//A�� input borrow�� �� ���� C�� �ִ´�
	*C = *A - *b;
	//printf("SUBAbB\n");
	/*
	* C�� borrow���� ���� ���� A = 0, b = 1�� ���� �� �� next borrow = 1
	* C�� B���� ���� ��� ������ �ϸ� next borrow = 1
	* �� �� �� ��츸 �Ͼ��, borrow�� 0 or 1�̹Ƿ� �� ��츦 or���� ���־ ����
	*/
	word borrow = ((*C < *b) | (*C < *B));
	//���������� A - b - B���� C�� ����
	*C -= *B;
	//next borrow�� ���� input borrow���� �־��ش�
	*b = borrow;
}

void SUBC(bigint** A, bigint** B, bigint** C) {//��ȣ ���忭 �� �ٸ��� ����

	bi_new(C, (*A)->wordlen);


	word i = 0;
	//�ʱ� borrow�� 0���� ����
	word b = 0;
	//�� �ڸ����� ����
	for (i = 0; i < (*A)->wordlen; i++) {
		SUBAbB(&(*A)->a[i], &(*B)->a[i], &(*C)->a[i], &b);
	}

}

void SUB(bigint** A, bigint** B, bigint** C) {//�Է°� üũ
	//��ȣ�� ���� ���

	if ((*A)->sign == (*B)->sign) {
		//printf("SUB\n");
		//A���� B�� Ŭ ��� ����� -
		if ((*A)->a[(*A)->wordlen - 1] < (*B)->a[(*B)->wordlen - 1]) {
			SUBC(B, A, C);
			(*C)->sign = NEGATIVE;
		}
		//A�� B���� Ŭ ��� ����� non_negative
		else SUBC(A, B, C);
	}
	//��ȣ�� �ٸ� ���
	else {
		//
		if (!((*A)->sign)) {
			(*B)->sign = NON_NEGATIVE;
			bigint_ADD(*A, *B, C);
		}
		else {
			(*C)->sign = NEGATIVE;
			(*A)->sign = NON_NEGATIVE;
			bigint_ADD(*A, *B, C);
		}
	}
}