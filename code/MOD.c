#include "MOD.h"

void ex_ltr_sq(bigint* x, bigint* n, bigint** t) {
	bi_set_one(t);
	for(int i=bi_get_bitlen(n)-1; i>=0; i--) {
		SchoolbookMUL(*t, *t, t);
		if(bi_get_ibit(n, i))
			SchoolbookMUL(*t, x, t);
		bi_refine(*t);
	}
}

void ex_ltr_mul(bigint* x, bigint* n, bigint** t) {
	bi_set_zero(t);
	for(int i=bi_get_bitlen(n)-1; i>=0; i--) {
		ADD(*t, *t, t);
		if(bi_get_ibit(n, i))
			ADD(*t, x, t);
	}
}

void ex_rtl_sq(bigint* x, bigint* n, bigint** t0) {
	bigint* t1 = NULL;
	bi_assign(&t1, x);
	bi_set_one(t0);
	for(int i=0; i<bi_get_bitlen(n); i++) {
		if(bi_get_ibit(n, i))
			SchoolbookMUL(*t0, t1, t0);
		SchoolbookMUL(t1, t1, &t1);
		bi_refine(*t0);
		bi_refine(t1);
	}
}

void ex_rtl_mul(bigint* x, bigint* n, bigint** t0) {
	bigint* t1 = NULL;
	bi_assign(&t1, x);
	bi_set_zero(t0);
	for(int i=0; i<bi_get_bitlen(n); i++) {
		if(bi_get_ibit(n, i))
			ADD(*t0, t1, t0);
		ADD(t1, t1, &t1);
	}
}

void MontRed(bigint* x, bigint* r, bigint* n, bigint* nn, bigint** t) {
	bigint* m = NULL;
	bigint* temp = NULL;
	bi_mod(x, bi_get_wordlen(r), &temp);
	SchoolbookMUL(temp, nn, &temp);
	bi_mod(temp, r, &m);
	
	SchoolbookMUL(m, n, &temp);
	ADD(temp, x, t);
	bi_rshift(t, bi_get_bitlen(r)-1);
	if(bi_compare(*t, n))
		SUB(*t, n, t);
}

void ModExp_by_MontRed(bigint* x, int e, bigint* n, bigint* nn, bigint* r, bigint* phil) {
	bigint* phix = NULL;
	bigint* temp = NULL;
	bi_assign(&temp, x);
	bi_lshift(&temp, bi_get_bitlen(r) - 1);
}