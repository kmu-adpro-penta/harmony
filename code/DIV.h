#ifndef __DIV_H__
#define __DIV_H__

#include "bigint.h"
#include "SUB.h"
#include "ADD.h"

word LDA(word A_1, word A_2, word B);
void DIVCC(bigint* A, bigint* B, word* Q, bigint** R);
void DIVC(bigint** A, bigint* B, bigint** Q, word i, int k);
void DIV(bigint* A, bigint* B, bigint** Q, bigint** R);
void  DIV_Naive(bigint* A, bigint* B, bigint** Q, bigint** R);


#endif //  __DIB_H__
