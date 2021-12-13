#include "MUL.h"

void AB(word* A, word* B, word* C0, word* C1) {
	word A0, A1, B0, B1, T, T0, T1, x;
	//x is w/2
	x = sizeof(word) * 4;
	//divide A B top, bottom w/2bit
	A1 = *A >> x;
	A0 = *A & ((1 << x) - 1);
	B1 = *B >> x;
	B0 = *B & ((1 << x) - 1);

	T0 = A0 * B1;
	T1 = A1 * B0;
	//T1 is T0 + T1 carry
	T0 += T1;
	T1 = T0 < T1;

	*C0 = A0 * B0;
	*C1 = A1 * B1;
	
	T = *C0;
	//*C0 + T0`s bottom w/2 bit
	*C0 += (T0 << x);
	//Because carry, compare T, *C0 thus *C1 + T0`s top w/2 bit + carry
	*C1 += (T1 << x) + (T0 >> x) + (*C0 < T);
}

void MULC(bigint* A, bigint* B, bigint** C) {
	int i, j;
	//For save AB
	bigint* T = NULL;
	bi_new(&T, A->wordlen + B->wordlen);
	if (T != NULL) {
		for (i = 0; i < A->wordlen; i++)
			for (j = 0; j < B->wordlen; j++)
			{
				//multiplication each word
				AB(&A->a[i], &B->a[j], &T->a[i + j], &T->a[i + j + 1]);
				//AB save in C
				ADDC(*C, T, C);
				//initialize T
				T->a[i + j] = 0;
				T->a[i + j + 1] = 0;
			}
		bi_delete(&T);
	}

	//C sign is A sign XOR B sign
	(*C)->sign = (A->sign) ^ (B->sign);
}
/*
* This is schoolbook multiplication
* multiplication each word and all addition
* result sign is
*	case 1 : A, B > 0 :
*		result > 0
*	case 2 : A, B < 0 :
*		result > 0
*	case 3 : A < 0, B > 0 :
*		result < 0
*	case 4 : A > 0, B < 0 :
*		result < 0
*/
void MUL(bigint* A, bigint* B, bigint** C) {
	//set bigint temp
	bigint* temp = NULL;
	bi_new(&temp, A->wordlen + B->wordlen);
	MULC(A, B, &temp);
	bi_refine(temp);
	//Put the result in C
	bi_assign(C, temp);
	bi_delete(&temp);
}
/*
* Karatsuba multiplication is faster than schoolbook multiplication
* The time complexity of schoolbook multiplication is O(n^2),
* The time complexity of Karatsuba multiplication is theoretically O(n^log2(3))
* A * B = (A1 * W^l + A0)(B1 * W^l + B0)
* = (A1 * B1 * W^2l + A0 * B0) + (A0 * B1 + A1 * B0) * W^l
* = (A1 * B1 * W^2l + A0 * B0) + ((A0 - A1) * (B1 - B0) + A0B0 + A1B1) * W^l
*/
void KaratsubaMUL(int f, bigint* A, bigint* B, bigint** C){
	if (!bi_compare(A, B))
		KaratsubaSq(f, A, C);
	bi_new(C, A->wordlen + B->wordlen);
	//If f is 0 or Either A or B is 0, stop karatsuba recursive
	if (!f || !(MIN(A->wordlen, B->wordlen))) 
		MULC(A, B, C);
	
	else {
		//Divide top, bottom bit
		int l = (MAX(A->wordlen, B->wordlen) + 1) >> 1;
		int i, sign;

		bigint* A0 = NULL;
		bigint* A1 = NULL;
		bigint* B0 = NULL;
		bigint* B1 = NULL;
		bigint* T0 = NULL;
		bigint* T1 = NULL;
		bigint* S = NULL;
		bigint* S0 = NULL;
		bigint* S1 = NULL;
		/*
		A1 = A >> lw, A0 = A % 2^lw
		B1 = B >> lw, B0 = B % 2^lw
		*/
		bi_new(&A0, MIN(A->wordlen, l));
		bi_new(&B0, MIN(B->wordlen, l));

		for (i = 0; i < MIN(A->wordlen, l); i++)
 			A0->a[i] = A->a[i];
		for (i = 0; i < MIN(B->wordlen, l); i++)
			B0->a[i] = B->a[i];
		bi_assign(&A1, A);
		bi_assign(&B1, B);
		bi_rshift(&A1, MIN(A->wordlen, l) * sizeof(word) * BYTE);
		bi_rshift(&B1, MIN(B->wordlen, l) * sizeof(word) * BYTE);
		//T1 = A1 * B1 * W^2l, T0 = A0 * B0
		KaratsubaMUL(f - 1, A1, B1, &T1);
		KaratsubaMUL(f - 1, A0, B0, &T0);

		bi_lshift(&T1, 2 * l * BYTE * sizeof(word));
		ADD(*C, T1, C);
		ADD(*C, T0, C);

		//S = ((A0 - A1)(B1 - B0) + A0 * B0 + A1 * B1) * W^l
		SUB(A0, A1, &S1);
		SUB(B1, B0, &S0);
		sign = S0->sign ^ S1->sign;
		S0->sign = 0;
		S1->sign = 0;
		KaratsubaMUL(f - 1, S1, S0, &S);
		S->sign = sign;

		bi_rshift(&T1, 2 * l * BYTE * sizeof(word));

		ADD(S, T1, &S);
		ADD(S, T0, &S);

		bi_lshift(&S, l * BYTE * sizeof(word));
		
		ADD(*C, S, C);

		bi_delete(&A0);
		bi_delete(&A1);
		bi_delete(&B0);
		bi_delete(&B1);
		bi_delete(&T0);
		bi_delete(&T1);
		bi_delete(&S);
		bi_delete(&S0);
		bi_delete(&S1);
	}

}

void A2(word* A, word* C0, word* C1) {
	word x, A0, A1, T, C;
	// x is w/2
	x = sizeof(word) * 4;
	//divide A top, bottom w/2bit
	A0 = *A & ((1 << x) - 1);
	A1 = *A >> x;

	*C0 = A0 * A0;
	*C1 = A1 * A1;

	T = A1 * A0;
	//C0 carry check
	C = *C0;
	// A1^2 + A0^2 + 2A1 * A0
	*C0 += (T << (x + 1));
	*C1 += (T >> (x - 1)) + (*C0 < C);
}

void Squaring(bigint* A, bigint** C) {
	int i, j;
	bigint* C0 = NULL;
	bigint* T0 = NULL;
	bi_new(&C0, A->wordlen * 2 - 1);
	bi_new(&T0, A->wordlen * 2 - 1);
	for (i = 0; i < A->wordlen; i++) {
		//each word square
		A2(&A->a[i], &(*C)->a[2 * i], &(*C)->a[2 * i + 1]);
		for (j = i + 1; j < A->wordlen; j++) {
			//Ai * Aj
			AB(&A->a[i], &A->a[j], &T0->a[i + j], &T0->a[i + j + 1]);
			ADD(C0, T0, &C0);
			T0->a[i + j] = 0;
			T0->a[i + j + 1] = 0;
		}
	}
	//each Ai * Aj has two
	bi_lshift(&C0, 1);
	ADD(*C, C0, C);
	bi_delete(&C0);
	bi_delete(&T0);
}
/*
* This is textbook Squaring
* Because in cryptography, squaring is used a lot, we are make square operation
*/
void TextbookSq(bigint* A, bigint** C) {
	bigint* temp = NULL;
	bi_new(&temp, A->wordlen * 2);
	Squaring(A, &temp);
	bi_refine(temp);
	bi_assign(C, temp);
	bi_delete(&temp);
}
/*
* This is Karatsuba Squaring
* A^2 = (A1 * W^l + A0)*(A1 * W^l + A0)
*	  = (A1^2 * W^2l + A0^2) + 2 * A0 * A1 * W^l
*/
void KaratsubaSq(int f, bigint* A, bigint** C) {
	bi_new(C, A->wordlen * 2);
	//If f is 0 or A is 0, stop karatsuba recursive
	if (!f || !A->wordlen)
		TextbookSq(A, C);

	else {
		//Divide top, bottom bit
		int l = (A->wordlen + 1) >> 1;
		int i;

		bigint* A0 = NULL;
		bigint* A1 = NULL;
		bigint* T0 = NULL;
		bigint* T1 = NULL;
		bigint* S = NULL;

		//A1 = A >> lw, A0 = A % 2 ^ lw
		bi_new(&A0, MIN(A->wordlen, l));

		for (i = 0; i < MIN(A->wordlen, l); i++)
			A0->a[i] = A->a[i];

		bi_assign(&A1, A);
		bi_rshift(&A1, MIN(A->wordlen, l) * sizeof(word) * BYTE);
		KaratsubaSq(f - 1, A1, &T1);
		KaratsubaSq(f - 1, A0, &T0);

		//A1^2 * W^2l + A0^2
		bi_lshift(&T1, 2 * l * BYTE * sizeof(word));
		ADD(*C, T1, C);
		ADD(*C, T0, C);

		//2 * A0 * A1 * W^l
		bi_rshift(&T1, 2 * l * BYTE * sizeof(word));
		MUL(A0, A1, &S);
		bi_lshift(&S, l * BYTE * sizeof(word) + 1);
		
		//A1^2 * W^2l + A0^2 + 2 * A0 * A1 * W^l
		ADD(*C, S, C);
		
		bi_delete(&A0);
		bi_delete(&A1);
		bi_delete(&T0);
		bi_delete(&T1);
		bi_delete(&S);
	}
}