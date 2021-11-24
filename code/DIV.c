#include "bigint.h"
#include "DIV.h"
#include "SUB.h"
#include "ADD.h"
#include "MUL.h"





//void shift(int arr[], int start, int end) {
//	int temp;
//	end = end - 1;
//	while (start < end) {
//		temp = arr[start];
//		arr[start] = arr[end];
//		arr[end] = temp;
//		start++;
//		end--;
//	}
//}
//void shiftLeft(int arr[], int d, int n) {
//	shift(arr, 0, d);
//	shift(arr, d, n);
//	shift(arr, 0, n);
//}





/*

Multi-Precision Long Division

이진 긴 나눗셈 알고리듬은 다중 워드 단위 긴 나눗셈 DIV로 확장할 수 있다.

2-word long division => DIVCC(A,B) => DIVC(A,B) => DIV(A,B)


*/



void LDA(word A_1, word A_2, word B, word* Q) {
	*Q = 0;
	word R = A_1;

	for (int j = sizeof(word) * 8 - 1; j > 0; j--) {
		word a_j = 1 << j;
		a_j = a_j & A_2;
		if (a_j == 0)
			a_j = 0;
		else
			a_j = 1;

		if ((R >> (sizeof(word) * 8 - 1)) > 0) {
			*Q = *Q + (1 << j);
			R = R + R - B + a_j;
		}
		else {
			R = R + R + a_j;
			if (R >= B) {
				*Q = *Q + (1 << j);
				R = R - B;
			}
		}
	}

}


/*

DIVCC(A,B)


*/

void DIVCC(bigint** A, bigint* B, word* Q, bigint** R) {


	if ((*A)->wordlen == B->wordlen) {
		*Q = (word)((*A)->a[(*A)->wordlen] / B->a[B->wordlen]);
	}
	else if ((*A)->wordlen == B->wordlen + 1) {
		if ((*A)->a[(*A)->wordlen] == B->a[B->wordlen]) {

			*Q = 65534;

		}
		else {
			LDA((*A)->a[(*A)->wordlen], (*A)->a[(*A)->wordlen - 1], B->a[B->wordlen], Q);
		}
	}

	bigint** Q_2 = NULL;
	word Q_array_1[1] = {*Q};
	bi_set_by_array(Q_2, NON_NEGATIVE, Q_array_1, 1);

	bigint** BQ = NULL;
	MULC(B, Q_2, BQ);
	SUB(*A,*BQ , R);

	while ((*R)->sign == NEGATIVE ) {
		Q--;
		ADD(*R, B, R);
	}
}





// ( Q, R )  <-  DIVC( R , B )
/*

Input : A, B	( A_j,B_j in [0,W), 0 <= A < B*W

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )


*/

void DIVC(bigint** A, bigint** B, bigint** Q, word i, int k) {

	if (bi_compare(*B, *A) == 1) {
		*((*Q)->a + i) = 0;
	}
	else {

		bi_lshift(A, k);
		bi_lshift(B, k);

		word* Q_2 = NULL;
		bigint** R_2 = NULL;

		DIVCC(A, B, Q_2, R_2);

		bi_rshift(R_2, k);

		bi_assign(A, R_2);
		*((*Q)->a + i) = Q_2;
	}




}

/*

Input : A,B ( 0 < A_j <= W )

Output : Q  ( A = BQ + R ( 0 <= R < B, 0 < Q_j <= W ))

*/



void DIV(bigint** A, bigint** B, bigint** Q, bigint** R) {



	if (bi_compare(*B,*A) == 1) {		// if A < B then

		bi_assign(R, *A);		// return (0,A)   :   A = 0 * B + A
		bi_set_zero(Q);

	}
	else {

		int k = 0;
		word B_most_num = (*B)->a[(*B)->wordlen - 1];
		while (k < sizeof(word) * 8) {
			if (1 <= (B_most_num >> (sizeof(word) * 8 - k - 1)) && (B_most_num >> (sizeof(word) * 8 - k - 1)) < 2)
				break;
			k++;
		}

		bi_new(Q, (*A)->wordlen - (*B)->wordlen + 1);
		bi_new(R, (*B)->wordlen);

		for (word i = (*A)->wordlen - 1; i > 0; i--) {

			bi_lshift(R, sizeof(word) * 8);

			*((*R)->a) = *((*A)->a + i);

			DIVC(R, B, Q, i, k);					// ( Q, R )  <-  DIVC( R , B )


		}
	}
}


