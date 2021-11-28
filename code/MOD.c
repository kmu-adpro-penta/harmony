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