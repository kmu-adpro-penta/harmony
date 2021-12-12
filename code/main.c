﻿#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#include "Mod.h"
#include <intrin.h>
#include <stdint.h>

#define MAIN

void toy1() {
	int i;
	srand(time(NULL));
	for (i = 0; i < 1000; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 100);
		
		bigint* B = NULL;
		//bi_gen_rand(&B, NON_NEGATIVE, 50);
		bigint* C = NULL;
		bigint* C1 = NULL;
		//printf("A = ");
		//bi_show_hex(A);
		//printf("\nB = ");
		//bi_show_hex(B);
		//printf("\nC = ");
		KaratsubaSq(flag, A, &C);
		TextbookSq(A, &C1);
		//bi_show_hex(C);
		if (bi_compare(C, C1)) {
			printf("error %d", i);
			printf("\n");
			bi_show_hex(A);
			printf("\n");
			bi_show_hex(C);
			printf("\n");
			bi_show_hex(C1);
			break;
		}
		bi_delete(&A);
		//bi_delete(&B);
		bi_delete(&C);
		bi_delete(&C1);

	}
}

void toy2() {
	for (int i = 0; i < LoopCTR; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 50);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 13);

		bigint* Q = NULL;
		bigint* R = NULL;

		printf("\n");
		printf("print(");
		bi_show_hex(A);
		printf(" // ");
		bi_show_hex(B);
		DIV_Naive(A, B, &Q, &R);
		printf(" == ");
		bi_show_hex(Q);
		printf(")");

		printf("\n");
		printf("print(");
		bi_show_hex(A);
		printf(" %% ");
		bi_show_hex(B);
		printf(" == ");
		bi_show_hex(R);
		printf(")");

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


void modt() {
	bigint* n = NULL;
	bigint* r = NULL;
	bigint* nn = NULL;
	bi_set_by_string(&n, NON_NEGATIVE, "3942ad939dedf");
	bi_set_one(&r);
	bi_lshift(&r, n->wordlen*sizeof(word)*BYTE);
	bi_show_hex(n);
	printf("\n");
	bi_show_hex(r);
	printf("\n");
	invN(n, r, &nn);
	bi_show_hex(nn);
	printf("\n");
}


int main() {
	toy1();
	/*
	clock_t after_ClockCycle, before_ClockCycle;
	
	//! Measure Clock Cycles
	before_ClockCycle = clock();
	toy2();
	after_ClockCycle = clock();
	
	printf("\n time = %fms", (double)(after_ClockCycle - before_ClockCycle) / LoopCTR);
	*/
	printf("ok");
	return 0;
}
