#ifndef __MOD_H__
#define __MOD_H__

#include "bigint.h"
#include "ADD.h"
#include "MUL.h"
#include "DIV.h"
#include "SUB.h"

void ex_ltr_sq(bigint* x, bigint* n, bigint** t);
void ex_ltr_mul(bigint* x, bigint* n, bigint** t);

void ex_rtl_sq(bigint* x, bigint* n, bigint** t0);
void ex_rtl_mul(bigint* x, bigint* n, bigint** t0);
void invN(bigint* n, bigint* r, bigint** nn);
void bi_expanded_euclid(bigint*a, bigint*b, bigint**x, bigint**y);

void MontRed(bigint* x, bigint* r, bigint* n, bigint* nn, bigint** t);
void ModExp_by_MontRed(bigint* x, bigint* e, bigint* n, bigint* nn, bigint* r, bigint* phi1, bigint** t);
#endif