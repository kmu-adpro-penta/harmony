#include "SUB.h"

void SUBAbB(word* A, word* B, word* C, word* b) {
	//*A - input borrow
	*C = *A - *b;
	/*
	* If A = 0 and b = 1 <=> A < b, next borrow is 1
	* If C < B, next borrow = 1
	* both can't happen at once, Thus calculation or
	*/
	word borrow = ((*A < *b) | (*C < *B));
	//*C = *A - b - *B
	*C -= *B;
	//Put next borrow in *b
	*b = borrow;
}

void SUBC(bigint* A, bigint* B, bigint** C) {

	int i;
	//if B->wordlen > A->wordlen, put 0 in SUBAbB instead of B
	word x = 0;
	//first borrow is 0
	word b = 0;
	//Subtract each word
	for (i=0; i < B->wordlen; i++)
		SUBAbB(&A->a[i], &B->a[i], &(*C)->a[i], &b);
	for (i=B->wordlen; i < A->wordlen; i++)
		SUBAbB(&A->a[i], &x, &(*C)->a[i], &b);

}
/*
* Bigint subtraction
* If A sign == B sign :
*	case 1 |A| >= |B| :
*		go to SUBC function
*	case 2 |A| < |B| :
*		go to SUBC function
*		result sign is negative
* If A sign != B sign :
*	case 1 A > 0 :
*		Set B sign is non negative and go to ADD function
*	case 2 A < 0 :
*		set A sign is non negative and go to ADD function
*		result sign is negative
*/
void SUB(bigint* A, bigint* B, bigint** C) {
	//set bigint temp
	bigint* temp = NULL;
	bi_new(&temp, MAX(A->wordlen, B->wordlen));
	//if sign is same
	if (A->sign == B->sign) {
		//|A| >= |B|
		if (bi_compare_abs(A, B) + 1) {
			SUBC(A, B, &temp);
			if(A->sign == -1)
				temp->sign = NEGATIVE;
		}
		//|A| < |B|
		else {
			SUBC(B, A, &temp);
			temp->sign = NEGATIVE;
		}
	}
	//if sign is different
	else {
		//A > 0
		if (!(A->sign)) {
			B->sign = NON_NEGATIVE;
			ADD(A, B, &temp);
		}
		//A < 0
		else {
			A->sign = NON_NEGATIVE;
			ADD(A, B, &temp);
			temp->sign = NEGATIVE;
		}
	}
	//Put the result in C
	bi_refine(temp);
	bi_assign(C, temp);
	bi_delete(&temp);
}