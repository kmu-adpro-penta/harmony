#include "MUL.h"

void AB(word* A, word* B, word* C0, word* C1) {
	word A0, A1, B0, B1, T, T0, T1, x;
	x = sizeof(word) * 4;// w/2
	A1 = *A >> x;
	A0 = *A - (A1 << x);
	B1 = *B >> x;
	B0 = *B - (B1 << x);
	// A B 상위 하위 w/2비트씩 쪼개기
	T0 = A0 * B1;
	T1 = A1 * B0;

	T0 += T1;
	T1 = T0 < T1;
	//T0에 값을 더하고 T1은 carry가 생기는지 여부
	*C0 = A0 * B0;
	*C1 = A1 * B1;
	T = *C0;
	//C0에는 T0의 하위 w/2비트만 더하고, C1에는 T0의 상위 w/2비트와 carry를 더함
	*C0 += (T0 << x);
	*C1 += (T1 << x) + (T0 >> x) + (*C0 < T);
}

void MULC(bigint* A, bigint* B, bigint** C) {
	word i, j;
	// AB연산을 받아줄 T 생성
	bigint* T = NULL;
	//C와 T의 크기를 나올 수 있는 최대치로 만들기
	bi_new(&T, A->wordlen + B->wordlen);
	if (T != NULL) {
		for (i = 0; i < A->wordlen; i++)
			for (j = 0; j < B->wordlen; j++)
			{
				//워드 단위로 곱셈 가짓수를 전부 실행
				AB(&A->a[i], &B->a[j], &T->a[i + j], &T->a[i + j + 1]);
				//C와 덧셈
				ADDC(*C, T, C);
				//다음 값을 온전히 받기 위해 T를 0으로
				T->a[i + j] = 0;
				T->a[i + j + 1] = 0;
			}
		//T를 다 썼으니 삭제
		bi_delete(&T);
	}

	//각 부호에 따라 C의 부호 결정 
	(*C)->sign = (A->sign) ^ (B->sign);
}

void SchoolbookMUL(bigint* A, bigint* B, bigint** C) {
	bigint* temp = NULL;
	bi_new(&temp, A->wordlen + B->wordlen);
	MULC(A, B, &temp);
	bi_refine(temp);
	bi_delete(C);
	*C = temp;
}

void KaratsubaMUL(int flag, bigint* A, bigint* B, bigint** C){
	bigint* A1 = NULL;
	bigint* B1 = NULL;
	printf("hello");
	bi_assign(&A1, A);
	bi_assign(&B1, B);
	bi_new(C, A1->wordlen + B1->wordlen);
	//사용자가 지정한 횟수 or A, B둘 중 한 값이 0이라면 재귀 빠져나가기
	printf("one");
	if (!flag || !(MIN(A1->wordlen, B1->wordlen))) 
		MULC(A1, B1, C);
	else {

		int l = (MAX(A1->wordlen, B1->wordlen) + 1) >> 1;
		int i, sign;
		/*
		A1 = A >> lw, A0 = A % 2^lw
		B1 = B >> lw, B0 = B % 2^lw
		*/
		bigint* A0 = NULL;
		bigint* B0 = NULL;
		bigint* T0 = NULL;
		bigint* T1 = NULL;
		bigint* S = NULL;
		bigint* S0 = NULL;
		bigint* S1 = NULL;

		bi_new(&A0, MIN(A->wordlen, l));
		bi_new(&B0, MIN(B->wordlen, l));

		for (i = 0; i < MIN(A->wordlen, l); i++)
			A0->a[i] = A1->a[i];
		for (i = 0; i < MIN(B->wordlen, l); i++)
			B0->a[i] = B1->a[i];
		printf("%d A0 = ", 2 - flag);
		bi_show_hex(A0);
		printf("\n%d B0 = ", 2 - flag);
		bi_show_hex(B0);
		printf("\n%d A = ", 2 - flag);
		bi_rshift(&A, MIN(A1->wordlen, l) * sizeof(word) * BYTE);
		bi_rshift(&B, MIN(B1->wordlen, l) * sizeof(word) * BYTE);
		bi_show_hex(A1);
		printf("\n%d B = ", 2 - flag);
		bi_show_hex(B1);
		printf("\n");
		//T1 = A1 * B1, T0 = A0 * B0
		KaratsubaMUL(flag - 1, A1, B1, &T1);
		KaratsubaMUL(flag - 1, A0, B0, &T0);

		printf("%d T1 = ", 2 - flag);
		bi_show_hex(T1);
		printf("\n%d T0 = ", 2 - flag);
		bi_show_hex(T0);
		printf("\n");
		// A1 * B1 + A0 * B0
		bi_lshift(&T1, 2 * l * BYTE * sizeof(word));//ㅠ
		ADD(*C, T1, C);
		ADD(*C, T0, C);

		//(A0 - A1)(B1 - B0)
		SUB(A0, A1, &S1);
		SUB(B1, B0, &S0);
		sign = S0->sign ^ S1->sign;
		S0->sign = 0;
		S1->sign = 0;
		KaratsubaMUL(flag - 1, S1, S0, &S);
		S->sign = sign;

		bi_rshift(&T1, 2 * l * BYTE * sizeof(word));
		ADD(S, T1, &S);
		ADD(S, T0, &S);

		bi_lshift(&S, l * BYTE * sizeof(word));

		ADD(*C, S, C);

		bi_delete(&A0);
		bi_delete(&B0);
		bi_delete(&T0);
		bi_delete(&T1);
		bi_delete(&S);
		bi_delete(&S0);
		bi_delete(&S1);
	}

}