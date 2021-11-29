#include "bigint.h"
#include "DIV.h"
#include "SUB.h"
#include "ADD.h"
#include "MUL.h"


int flag = 0;



/*

Multi-Precision Long Division

이진 긴 나눗셈 알고리듬은 다중 워드 단위 긴 나눗셈 DIV로 확장할 수 있다.

2-word long division => DIVCC(A,B) => DIVC(A,B) => DIV(A,B)


*/



word LDA(word A_1, word A_0, word B) {

	word Q = 0;
	word R = A_1;

	for (int j = sizeof(word) * 8 - 1; j > -1; j--) {
		word a_j = 1 << j;
		a_j = a_j & A_0;
		if (a_j == 0)
			a_j = 0;
		else
			a_j = 1;

		if ((R >> (sizeof(word) * 8 - 1)) > 0) {
			Q = Q + (1 << j);
			R = R + a_j - (B-R);
		}
		else {
			R = 2*R + a_j;
			if (R >= B) {
				Q = Q + (1 << j);
				R = R - B;
			}
		}
	}

	return Q;

}


/*

DIVCC(A,B)


*/

void DIVCC(bigint** A, bigint* B, word* Q, bigint** R) {

	if ((*A)->wordlen == B->wordlen) {
		*Q = (*A)->a[B->wordlen-1] / B->a[B->wordlen-1] ;
	}
	else if ((*A)->wordlen == B->wordlen + 1) {

		if ( (*A)->a[B->wordlen] == B->a[B->wordlen-1] ) {

			*Q = 65534;

		}
		else {
			*Q = LDA((*A)->a[B->wordlen], (*A)->a[B->wordlen - 1], B->a[B->wordlen-1]);
		}
	}


	if (flag) {
		printf("\nQ = %d", *Q);
	}



	bigint* Q_temp = NULL;
	word Q_temp_array_1[1] = {*Q};
	bi_set_by_array(&Q_temp, NON_NEGATIVE, Q_temp_array_1, 1);


	bigint* BQ = NULL;
	SchoolbookMUL(B, Q_temp, &BQ);
	bi_refine(BQ);

	bigint* A_minus_BQ = NULL;

	SUB(*A, BQ , &A_minus_BQ);

	bigint* R_temp = NULL;

	while (A_minus_BQ->sign == NEGATIVE) {

		(*Q)--;


		ADD(A_minus_BQ, B, &R_temp);		// R = R+B		R<0

		bi_assign(&A_minus_BQ, R_temp);

		R_temp->sign = NON_NEGATIVE;

	}
	
	bi_assign(R,A_minus_BQ);


	bi_delete(&Q_temp);
	bi_delete(&BQ);
	bi_delete(&A_minus_BQ);


}





// ( Q, R )  <-  DIVC( R , B )
/*

Input : A, B	( A_j,B_j in [0,W), 0 <= A < B*W

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )


*/

void DIVC(bigint** A, bigint* B, bigint** Q, word i, int k) {

	if (bi_compare(B, *A) == 1) {
		(*Q)->a[i] = 0;
	}
	else {
		bigint* B_temp = NULL;
		bi_assign(&B_temp, B);
		bi_lshift(&B_temp, k);

		bigint* A_temp = NULL;
		bi_assign(&A_temp, *A);
		bi_lshift(&A_temp, k);

		word Q_2 = 0;
		bigint* R_temp = NULL;

		DIVCC(&A_temp, B_temp, &Q_2, &R_temp);

		bi_rshift(&R_temp, k);

		bi_assign(A, R_temp);
		
		(*Q)->a[i] = Q_2;


		bi_delete(&R_temp);
		bi_delete(&B_temp);
		bi_delete(&A_temp);

		

	}



}

/*

Input : A,B ( 0 < A_j <= W )

Output : Q  ( A = BQ + R ( 0 <= R < B, 0 < Q_j <= W ))

*/



void DIV(bigint* A, bigint* B, bigint** Q, bigint** R) {


	if (bi_compare(B,A) == 1) {		// if A < B then

		bi_assign(R, A);		// return (0,A)   :   A = 0 * B + A
		bi_set_zero(Q);

	}
	else {

		word k = 0;
		word B_most_num = B->a[B->wordlen - 1];
		while (k < sizeof(word) * 8) {
			if (1 <= (B_most_num >> (sizeof(word) * 8 - k - 1)) && (B_most_num >> (sizeof(word) * 8 - k - 1)) < 2)
				break;
			k++;
		}

		bi_new(Q, A->wordlen - B->wordlen + 1);
		bi_new(R, B->wordlen);



		for (int i = A->wordlen - 1; i > -1; i--) {

			bi_lshift(R, sizeof(word) * 8);

			(*R)->a[0] = A->a[i];

			DIVC(R, B, Q, i, k);					// ( Q, R )  <-  DIVC( R , B )

		}

	}
	bi_refine(*R);
	bi_refine(*Q);

}




