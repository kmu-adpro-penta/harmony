#include "bigint.h"
#include <stdio.h>
#include "SUB.h"


void shift(int arr[], int start, int end) {
	int temp;
	end = end - 1;
	while (start < end) {
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}
void shiftLeft(int arr[], int d, int n) {
	shift(arr, 0, d);
	shift(arr, d, n);
	shift(arr, 0, n);
}





/*

Multi-Precision Long Division

���� �� ������ �˰����� ���� ���� ���� �� ������ DIV�� Ȯ���� �� �ִ�.

2-word long division => DIVCC(A,B) => DIVC(A,B) => DIV(A,B)


*/

void LDA(word A_1,word A_2,word B) {
	word Q = 0;
	word R = A_1;

	for (int j = sizeof(word) - 1; j > 0; j--) {

	}

}


/*

DIVCC(A,B)


*/

void DIVCC(bigint** A, bigint* B, word* Q, bigint** R) {


	if ((*A)->wordlen == B->wordlen) {
		LDA();
	}	
	else if ((*A)->wordlen == (*B).wordlen + 1) {
		if (*((*A)->a+(*A)->wordlen-1) == *(B->a + B->wordlen - 1)) {
			word num = 0;
			Q = num - 2;
		}
		else {
			LDA();
		}
	}
	SUB(A, mul(B, Q),R);
	while (R < 0) {

	}


}





// ( Q, R )  <-  DIVC( R , B )
/*

Input : A, B	( A_j,B_j in [0,W), 0 <= A < B*W

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )


*/

void DIVC(bigint **A,bigint *B,bigint ** Q,word i,int k) {

	if (bi_compare(B, A)) {
		*((*Q)->a + i) = 0;
	}
	else {
		bigint** A_2 = NULL;
		bigint** B_2 = NULL;
		bi_assign(A_2, *A);
		bi_assign(B_2, B);
		
		bi_lshift(A_2, k);
		bi_lshift(B_2, k);

		word* Q_2 = NULL;
		bigint** R_2 = NULL;

		DIVCC(A_2,B_2,Q,R_2);

		bi_rshift(R_2, k);

		bi_assign(A, R_2);
	}


}

/*

Input : A,B ( 0 < A_j <= W )

Output : Q  ( A = BQ + R ( 0 <= R < B, 0 < Q_j <= W ))

*/



void DIV(bigint* A, bigint* B, bigint** Q, bigint** R) {



	if (bi_compare(B, A)) {		// if A < B then

		bi_new(R, A->wordlen);
		bi_assign(R, A);		// return (0,A)   :   A = 0 * B + A
		bi_set_zero(Q);
		
	}
	else {

		int k = 0;
		word B_most_num = *(B->a + B->wordlen - 1);

		for (k; k < sizeof(word); k++)
			if (1 <= (B_most_num >> (sizeof(word) - k - 1)) && (B_most_num >> (sizeof(word) - k - 1)) < 2)
				break;

		bi_new(Q, A->wordlen - B->wordlen + 1);
		bi_new(R, B->wordlen);
		
		for (word i = A->wordlen; i > 0; i++) {
			
			
			bi_rshift(R,sizeof(word));
			
			*((*R)->a) = A->a + i;
			
			DIVC(R, B, Q,i,k);					// ( Q, R )  <-  DIVC( R , B )
			
		}
	}
}


