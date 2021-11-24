#include "MUL.h"

void AB(word* A, word* B, word* C0, word* C1) {
	word A0, A1, B0, B1, T, T0, T1, x;
	x = sizeof(word) * 4;// w/2
	A1 = *A >> x;
	A0 = *A - (A1 << x);
	B1 = *B >> x;
	B0 = *B - (B1 << x);
	// A B ���� ���� w/2��Ʈ�� �ɰ���
	T0 = A0 * B1;
	T1 = A1 * B0;

	T0 += T1;
	T1 = T0 < T1;
	//T0�� ���� ���ϰ� T1�� carry�� ������� ����
	*C0 = A0 * B0;
	*C1 = A1 * B1;
	T = *C0;
	//C0���� T0�� ���� w/2��Ʈ�� ���ϰ�, C1���� T0�� ���� w/2��Ʈ�� carry�� ����
	*C0 += (T0 << x);
	*C1 += (T1 << x) + (T0 >> x) + (*C0 < T);
}

void MULC(bigint* A, bigint* B, bigint** C) {
	word i, j;
	// AB������ �޾��� T ����
	bigint* T = NULL;
	//T�� C�� ũ�⸦ ���� �� �ִ� �ִ�ġ�� �����
	bi_new(C, A->wordlen + B->wordlen);
	bi_new(&T, A->wordlen + B->wordlen);
	if (T != NULL) {
		for (i = 0; i < A->wordlen; i++)
			for (j = 0; j < B->wordlen; j++)
			{
				//���� ������ ���� �������� ���� ����
				AB(&A->a[i], &B->a[j], &T->a[i + j], &T->a[i + j + 1]);
				//C�� ����
				ADDC(*C, T, C);
				//���� ���� ������ �ޱ� ���� T�� 0����
				T->a[i + j] = 0;
				T->a[i + j + 1] = 0;
			}
		//T�� �� ������ ����
		bi_delete(T);
	}
	//�� ��ȣ�� ���� C�� ��ȣ ���� 
	(*C)->sign = (A->sign) ^ (B->sign);
}

