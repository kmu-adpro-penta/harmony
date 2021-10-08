#include <iostream>
#include <stdlib.h>



using namespace std;

//bool - > 비트 단위로 처리하기위한 자료형 

typedef unsigned int word;

typedef struct {
	int sign;
	int wordlen;
	word* a;
} bigint;

word ADD_mod(word A, word B) {
	return (A + B) >> 5;
}

word ADD_ABc(word *A, word *B,word c) {
	word c_2 = 0;
	word C = *A + *B;
	if (C < *A) {
		c_2 = 1;
	}
	C = C + c;
	if (C < c) {
		c_2 += 1;
	}
	return c_2, C;
}

/*
bigint* ADDC(bigint* A, bigint* B) {

	for (word i = A->wordlen - B->wordlen; i < A->wordlen; i++) {
		*(B->a+i) = 0;   
	}

	word c = 0;
	bigint *C;
	// bigint C 메모리 할당
	C->sign = 0;
	C->wordlen = A->wordlen;

	for (word j = 0; j < A->wordlen; j++) {
		c,*(C->a+j) = ADD_ABc(A->a+j, B->a + j,c);
	}

	*(C->a + A->wordlen) = c;

	if (*(C->a + A->wordlen) == 1) {
		C->wordlen = A->wordlen;
		//A,B 메모리 삭제
		return C;
	}
	else {
		C->wordlen = A->wordlen - 1;
		//A,B, 메모리 삭제
		return C;
	}

}

bigint* SUB(bigint* A, bigint* B) {

}

bigint* ADD(bigint* A, bigint* B) {
	if (*(A->a) == 0)
		return B;

	if (*(B->a) == 0)
		return A;

	if (A->sign > 0 && B->sign < 0) {
		B->sign = 1;
		return SUB(A, B);
	}
	if (A->sign < 0 && B->sign > 0) {
		A->sign = 1;
		return SUB(B, A);
	}

	if (A->wordlen >= B->wordlen)
		return ADDC(A, B);
	else
		return ADDC(B, A);
}
*/
int main() {

	return 0;


}
