#include "MUL.h"

void AB(word* A, word* B, word* C0, word* C1) {
	word A0, A1, B0, B1, T, T0, T1, x;
	x = sizeof(word) * 4;// w/2

	A0 = (*A << x);
	A0 = A0 >> x;
	A1 = *A >> x;

	B0 = *B << x;
	B0 = B0 >> x;
	B1 = *B >> x;
	// A B 상위 하위 w/2비트씩 쪼개기
	T0 = A0 * B1;
	T1 = A1 * B0;

	T0 += T1;
	T1 = T0 < T1;

	*C0 = A0 * B0;
	*C1 = A1 * B1;
	T = *C0;

	*C0 += (T0 << x);
	*C1 += (T1 << x) + (T0 >> x) + (*C0 < T);
}

void MULC(bigint** A, bigint** B, bigint** C) {
	word i, j;
	bigint* T = NULL;
	bi_realloc(C, MIN((*A)->wordlen, (*B)->wordlen));
	bi_new(&T, (*A)->wordlen + (*B)->wordlen);
	if (T != NULL) {
		for (i = 0; i < (*A)->wordlen; i++)
			for (j = 0; j < (*B)->wordlen; j++)
			{
				AB(&(*A)->a[i], &(*B)->a[j], &T->a[i + j], &T->a[i + j + 1]);
				ADDC(*C, T, C);
				T->a[i + j] = 0;
				T->a[i + j + 1] = 0;
			}
		bi_delete(T);
	}
	(*C)->sign = (*A)->sign ^ (*B)->sign;
}
