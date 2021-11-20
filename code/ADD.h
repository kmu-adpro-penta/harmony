#ifndef __ADD_H__
#define __ADD_H__

#include "bigint.h"

word ADD_ABc(word A, word B, word c, word* C_j);
void ADDC(bigint* A, bigint* B,bigint** C);
void bigint_ADD(bigint* A, bigint* B,bigint **C);

#endif
