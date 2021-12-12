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

		DIV(A, B, &Q,&R);
		//bi_show_hex(C);

		bi_delete(&A);
		bi_delete(&B);
		bi_delete(&Q);
		bi_delete(&R);
	}
}

void toy2() {
	for (int i = 0; i < LoopCTR; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 100);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 40);

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


void modt() {
	bigint* n = NULL;
	bigint* r = NULL;
	bigint* nn = NULL;
	bigint* temp = NULL;
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

	bigint* phi1 = NULL;
	DIV(r, n, &temp, &phi1);
	bi_show_hex(phi1);
	printf("\n");

	bigint* x = NULL;
	bigint* e = NULL;
	bi_set_by_string(&x, NON_NEGATIVE, "17081f820b5ad");
	bi_set_by_string(&e, NON_NEGATIVE, "7281a");
	bi_show_hex(x);
	printf("\n");
	bi_show_hex(e);
	printf("\n");

	bigint* answer = NULL;

	ModExp_by_MontRed(x, e, n, nn, r, phi1, &answer);
	bi_show_hex(answer);
	printf("\n");
}


int main() {
	//modt();
	
	clock_t after_ClockCycle, before_ClockCycle;
	
	//! Measure Clock Cycles
	before_ClockCycle = clock();
	toy2();
	after_ClockCycle = clock();
	
	printf("\n time = %fms", (double)(after_ClockCycle - before_ClockCycle) / LoopCTR);
	
	return 0;
}
