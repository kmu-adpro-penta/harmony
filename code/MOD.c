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
	bi_mod(temp, bi_get_wordlen(r), &m);
	SchoolbookMUL(m, n, &temp);
	ADD(temp, x, t);
	bi_rshift(t, bi_get_bitlen(r)-1);
	if(bi_compare(*t, n))
		SUB(*t, n, t);
}

void ModExp_by_MontRed(bigint* x, bigint* e, bigint* n, bigint* nn, bigint* r, bigint* phi1) {
	bigint* phix = NULL;
	bigint* temp = NULL;
	bi_assign(&temp, x);
	bi_lshift(&temp, bi_get_bitlen(r) - 1);
	bigint* q = NULL;
	DIV(temp, n, &q ,&phix);
	int l = bi_get_bitlen(e) - 1;

	bigint* t = NULL;
	bi_assign(&t, phi1);

	while(l > -1) {
		SchoolbookMUL(t, t, &t);
		MontRed(t, r, n, n, &t);
		bi_rshift(&e, 1);
		if (e->a[0] & 0x1) {
			SchoolbookMUL(t, phix, &t);
			MontRed(t, r, n, nn, &t);
		}
		l--;
	}
	MontRed(t, r, n, nn, &t);
}

void invN(bigint* n, bigint* r, bigint** nn) {
	bigint* x = NULL;
	bigint* y = NULL;
	bi_expanded_euclid(r, n, &x, &y);
	DIV(y, r, &x, nn);
	bi_delete(&x);
	bi_delete(&y);
}

void bi_expanded_euclid(bigint*a, bigint*b, bigint**x, bigint**y) {
	bigint* r1=NULL;
	bigint* r2=NULL;
	bigint* s1=NULL;
	bigint* s2=NULL;
	bigint* t1=NULL;
	bigint* t2=NULL;
	bigint* q=NULL;
	bigint* r=NULL;
	bigint* temp=NULL;

	if(bi_compare(a, b) == -1) {
		bi_assign(&r1, b);
		bi_assign(&r2, a);
	} else {
		bi_assign(&r1, a);
		bi_assign(&r2, b);
	}
	bi_set_one(&s1);
	bi_set_zero(&s2);
	bi_set_zero(&t1);
	bi_set_one(&t2);

	while(!bi_is_zero(r2)) {
		//GCD
		printf("NONO");
		DIV(r1, r2, &q, &r);
		bi_assign(&r1, r2);
		bi_assign(&r2, r);
		/* 
		s1 = s2 , s2 = s1 - q * s2
		*/
		SchoolbookMUL(q, s2, &temp);
		SUB(s1, temp, &temp);
		bi_assign(&s1, s2);
		bi_assign(&s2, temp);
		/*
		t1 = t2 , t2 = t1 - q * t2
		*/
		SchoolbookMUL(q, t2, &temp);
		SUB(t1, temp, &temp);
		bi_assign(&t1, s2);
		bi_assign(&t2, temp);
	}
	printf("end)");
	if(bi_compare(a, b) == -1) {
		bi_assign(y, s1);
		bi_assign(x, t1);
	} else {
		bi_assign(x, s1);
		bi_assign(y, t1);
	}
	
	bi_delete(&r1);
	bi_delete(&r2);
	bi_delete(&s1);
	bi_delete(&s2);
	bi_delete(&t1);
	bi_delete(&t2);
	bi_delete(&q);
	bi_delete(&r);
	bi_delete(&temp);
}