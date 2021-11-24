#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
//#include "DIV.h"
#define MAIN
int main() {
	srand((unsigned)time(NULL));
	bigint* A = NULL;
	bi_gen_rand(&A);
	//bi_new(&A, 2);
	//word x0[2] = { 0x10eb, 0x8d27 };
	//bi_set_by_array(&A, 0, x0, 2);

	bigint* B = NULL;
	bi_gen_rand(&B);
	//bi_new(&B, 8);
	//word x1[12] = { 0x8e53, 0x17b9, 0xe60d, 0x685d, 0xcfa2, 0x2ee8,
	//0xb05f, 0x943b};
	//bi_set_by_array(&B, 0, x1, 8);
	bigint* C = NULL;
	printf("A = ");
	bi_show_hex(A);
	printf("\nB = ");
	bi_show_hex(B);
	SUB(A, B, &C);
	bi_refine(C);
	printf("\nC = ");
	bi_show_hex(C);

	return 0;
}