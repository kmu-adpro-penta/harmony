#ifndef __MUL_H__  // !__MUL_H__
#define __MUL_H__
#include "ADD.h"
#include "SUB.h"
#include "bigint.h"

void AB(word* A, word* B, word* C0, word* C1);
void MULC(bigint* A, bigint* B, bigint** C);
void SchoolbookMUL(bigint* A, bigint* B, bigint** C);
void KaratsubaMUL(int* flag, bigint* A, bigint* B, bigint** C);
#endif
