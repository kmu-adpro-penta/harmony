#include "bigint.h"
#include "DIV.h"
#include "SUB.h"
#include "ADD.h"
#include "MUL.h"



/*

Multi-Precision Long Division

binary long division algorithm can expand multiple words long division

2-word long division => DIVCC(A,B) => DIVC(A,B) => DIV(A,B)

*/

/*
Long Division Algorithm

Input : A = A_1 * W + A_0	, B ( A_1,B_0 in [0,W), w-1 <= B`s bit length < w )

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )

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
DIVCC

Input : A, B	( A_j,B_j in [0,W), 0 <= A < B*W ) , ( A wordlen = n , B의 wordlen = m )

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )

*/

void DIVCC(bigint** A, bigint* B, word* Q, bigint** R) {

	//If A wordlen = B wordlen, Q = A_(m-1) / B_(m-1)
	if ((*A)->wordlen == B->wordlen)
		*Q = (*A)->a[B->wordlen-1] / B->a[B->wordlen-1] ;

	//If A wordlen = B wordlen + 1
	else if ((*A)->wordlen == B->wordlen + 1) {
		//If A_m = B_(m-1)
		if ( (*A)->a[B->wordlen] == B->a[B->wordlen-1] )
			bi_max_number(Q);
		//If  A_m != B_(m-1)
		else
			*Q = LDA((*A)->a[B->wordlen], (*A)->a[B->wordlen - 1], B->a[B->wordlen-1]);
	}

	// R = A - B * Q
	bigint* Q_temp = NULL;
	word Q_temp_array_1[1] = {*Q};
	bi_set_by_array(&Q_temp, NON_NEGATIVE, Q_temp_array_1, 1);

	bigint* BQ = NULL;
	MUL(B, Q_temp, &BQ);
	bi_refine(BQ);

	bigint* A_minus_BQ = NULL;
	SUB(*A, BQ , &A_minus_BQ);
	bigint* R_temp = NULL;

	//If R < 0
	while (A_minus_BQ->sign == NEGATIVE) {
		// Q <- Q - 1
		(*Q)--;

		// R <- R + B
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

Input : A, B	( A_j,B_j in [0,W), 0 <= A < B*W )

Output : Q, R	( such that A = B*Q + R ( 0 <= R < B , Q in [0,W) )


*/
void DIVC(bigint** A, bigint* B, bigint** Q, word i, int k) {

	// A와 B를 비교하는 단계
	// 만일 B가 A보다 크다면 Q = 0 , R = A 를 반환합니다.
	if (bi_compare(B, *A) == 1) {
		(*Q)->a[i] = 0;
	}
	else {

		//B_temp에 2^k * B 를 대입
		bigint* B_temp = NULL;
		bi_assign(&B_temp, B);
		bi_lshift(&B_temp, k);

		//A_temp에 2^k * A 를 대입
		bigint* A_temp = NULL;
		bi_assign(&A_temp, *A);
		bi_lshift(&A_temp, k);

		//Q_2와 R_temp를 정의
		word Q_2 = 0;
		bigint* R_temp = NULL;

		// Q_2 , R_temp  <-   DIVCC(A_temp.B_temp)
		DIVCC(&A_temp, B_temp, &Q_2, &R_temp);

		//R에 2^(-k) * R_temp 를 대입
		bi_rshift(&R_temp, k);
		bi_assign(A, R_temp);
		
		//Q의 i번째 원소에 Q_2를 대입
		(*Q)->a[i] = Q_2;

		//사용을 다한 메모리값 해제
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

	// A와 B를 비교하는 단계
	// 만일 B가 A보다 크다면 Q = 0 , R = A 를 반환합니다.
	if (bi_compare(B,A) == 1) {		
		bi_assign(R, A);
		bi_set_zero(Q);
	}
	else {

		//DIVC의 k값을 DIV에서 먼저 계산하여 할당한 후 DIVC로 전달하여 줍니다.
		word k = 0;		word B_most_num = B->a[B->wordlen - 1];
		while (k < sizeof(word) * 8) {
			if (1 <= (B_most_num >> (sizeof(word) * 8 - k - 1)) && (B_most_num >> (sizeof(word) * 8 - k - 1)) < 2)
				break;
			k++;
		}

		//Q와 R에 값을 입력하기 위해 메모리를 할당하여 줍니다.
		bi_new(Q, A->wordlen - B->wordlen + 1);		bi_new(R, B->wordlen);


		//A의 길이 만큼 실행해줍니다.
		for (int i = A->wordlen - 1; i > -1; i--) {
			bi_lshift(R, sizeof(word) * 8);			// R <- R*W
			(*R)->a[0] = A->a[i];					// R <- R + A_i
			DIVC(R, B, Q, i, k);					// ( Q, R )  <-  DIVC( R , B )
		}
	}

	//R과 Q의 필요없는 0제거
	bi_refine(*R);
	bi_refine(*Q);

}




/*

Division Algorithm (Naive Version)

Input : A,B ( A,B in Z)

Output : INAVALID ( A = BQ + R ( 0 <= R < B ))

*/

void  DIV_Naive(bigint* A, bigint* B,bigint** Q,bigint** R) {

	// B <= 0 인 경우 INVALID
	if (B->sign == NEGATIVE || bi_is_zero(B) == TRUE)
		printf("\nINVALID INPUT VALUE\n");
	// A < B 인 경우
	else if (bi_compare(B, A) == 1) {
		// ( Q , R )  <-  ( 0 , A )
		bi_set_zero(Q);
		bi_assign(R, A);
	}
	// B = 1 인경우
	else if (bi_is_one(B)) {
		// ( Q , R )  <-  ( A , 0 )
		bi_assign(Q, A);
		bi_set_zero(R);
	}
	else {
		// ( Q , R )  <-  ( 0 , A )
		bi_set_zero(Q);
		bi_assign(R, A);

		bigint* Q_temp = NULL;
		word Q_temp_array_1[1] = { 1 };
		bi_set_by_array(&Q_temp, NON_NEGATIVE, Q_temp_array_1, 1);

		bigint* R_temp = NULL;

		// R >= B 인 경우
		while (bi_compare(*R,B) == 1) {
			// ( Q , R )  <-  ( Q + 1 , R - B )
			ADD(*Q, Q_temp, Q);
			SUB(*R, B, &R_temp);
			bi_assign(R, R_temp);
		}

		//사용이 끝난 메모리 해제
		bi_delete(&R_temp);
		bi_delete(&Q_temp);
	}
}