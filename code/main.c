#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#include <intrin.h>
#include <stdint.h>

#define MAIN

void toy1() {
	int i;
	for (i = 0; i < 10; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 5);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 2);
		bigint* Q = NULL;
		bigint* R = NULL;

		//printf("A = ");
		//bi_show_hex(A);
		//printf("\nB = ");
		//bi_show_hex(B);
		//printf("\nC = ");

		ADD(A, B, &Q,&R);
		//bi_show_hex(C);

		bi_delete(&A);
		bi_delete(&B);
		bi_delete(Q);
		bi_delete(R);
	}
}

void toy2() {
	for (int i = 0; i < LoopCTR; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 100);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 30);

		bigint* Q = NULL;
		bigint* R = NULL;

		//printf("\n");
		//printf("print(");
		//bi_show_hex(A);
		//printf(" // ");
		//bi_show_hex(B);
		DIV(A, B, &Q, &R);
		//printf(" == ");
		//bi_show_hex(Q);
		//printf(")");

		//printf("\n");
		//printf("print(");
		//bi_show_hex(A);
		//printf(" %% ");
		//bi_show_hex(B);
		//printf(" == ");
		//bi_show_hex(R);
		//printf(")");

		bi_delete(&A);
		bi_delete(&B);
		bi_delete(&Q);
		bi_delete(&R);
		

	}

}

void toy3() {
	bigint* C = NULL;
	bigint* D = NULL;
	bigint** A = NULL;
	bi_gen_rand(&C, NON_NEGATIVE, 3);


	bi_assign(&D, C);
	bi_assign(A, C);


}

// return current clock cycles
uint64_t clockcycles()
{
	return __rdtsc();
}

int main() {
	
	clock_t after_ClockCycle, before_ClockCycle;
	
	//! Measure Clock Cycles
	before_ClockCycle = clock();
	toy2();
	after_ClockCycle = clock();
	
	printf("\n time = %fms", (double)(after_ClockCycle - before_ClockCycle) / LoopCTR);
	return 0;

}