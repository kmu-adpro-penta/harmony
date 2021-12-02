#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#include <intrin.h>
#include <stdint.h>

#define MAIN



void Bigint_test() {
	for (int i = 0; i < 10; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 5);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 3);

		//bigint* C = NULL;

		bigint* Q = NULL;
		bigint* R = NULL;

		DIV_Naive(A, B, &Q, &R);
		//MUL(A, B, &C);
		//ADD(A, B, &C);

		//printf("\n");
		//printf("print(");
		//bi_show_hex(A);
		//printf(" // ");
		//bi_show_hex(B);
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
		//bi_delete(&C);
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
	before_ClockCycle = clockcycles();
	Bigint_test();
	after_ClockCycle = clockcycles();
	
	printf("\n [ Bigint_test ] \n ClockCylce = %lld", (after_ClockCycle - before_ClockCycle) / LoopCTR);



	return 0;
}
