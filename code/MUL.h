#ifndef __MUL_H__  // !__MUL_H__
#define __MUL_H__
#include "ADD.h"
#include "SUB.h"
#include "bigint.h"

void AB(word* A, word* B, word* C0, word* C1);
void MULC(bigint* A, bigint* B, bigint** C);
void MUL(bigint* A, bigint* B, bigint** C);
void KaratsubaMUL(int f, bigint* A, bigint* B, bigint** C);
void A2(word* A, word* C0, word* C1);
void Squaring(bigint* A, bigint** C);
void TextbookSq(bigint* A, bigint** C);
#endif
