#include "bigint.h"
#include <stdio.h>

/*

Multi-Precision Long Division

���� �� ������ �˰����� ���� ���� ���� �� ������ DIV�� Ȯ���� �� �ִ�.

2-word long division => DIVCC(A,B) => DIVC(A,B) => DIV(A,B)


*/


/*

Input : A, B	( A_j,B_j in [0,W), 0 <= A < B*W

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )


*/
void DIVC(bigint* A, bigint* B, word* Q_j) {

	if (*(A->a + A->wordlen) < *(B->a + B->wordlen))
		*Q_j = 0;
	else {

	}
}

/*

Input : A,B ( 0 < A_j <= W )

Output : Q  ( A = BQ + R ( 0 <= R < B, 0 < Q_j <= W ))

*/

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R) {

	if (A->wordlen < B->wordlen)
		bi_assign(R, A);
	else {

		bi_new(R, B->wordlen);

		for (int i = A->wordlen-1; i > 0; i--) {

			bi_lshift(R, sizeof(word));		// R = R * W
			*((*R)->a) += *(A->a + i);		// R = R + A_i

			DIVC(R, B, (*Q)->a + i);					// ( Q_i, R ) <- DIVC(R,B)

		}
	}


}