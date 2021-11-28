#ifndef __MOD_H__
#define __MOD_H__

#include "bigint.h"
#include "ADD.h"
#include "MUL.h"

void ex_ltr_sq(bigint* x, bigint* n, bigint** t);
void ex_ltr_mul(bigint* x, bigint* n, bigint** t);

void ex_rtl_sq(bigint* x, bigint* n, bigint** t0);
void ex_rtl_mul(bigint* x, bigint* n, bigint** t0);

#endif