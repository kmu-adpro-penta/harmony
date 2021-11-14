#include "bigint.h"
#include <stdio.h>

/*

Multi-Precision Long Division

���� �� ������ �˰����� ���� ���� ���� �� ������ DIV�� Ȯ���� �� �ִ�.

2-word long division => DIVCC(A,B) => DIVC(A,B) => DIV(A,B)


*/


/*

Input : A,B ( 0 < A_j <= W )

Output : Q  ( A = BQ + R ( 0 <= R < B, 0 < Q_j <= W ))

*/

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R) {

	if (A->wordlen < B->wordlen)
		bi_assign(R, A);
	else {

		bi_new(R, B->wordlen);

		for (int i = A->wordlen; i > 0; i--) {
			bi_rshift(R, 1);
			*((*R)->a) += *(A->a + i);
			DIVC(R, B, Q);

		}
	}


}