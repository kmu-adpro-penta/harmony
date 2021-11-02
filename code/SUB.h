#ifndef __SUB_H__  // !__SUB_H__
#define __SUB_H__
#include "ADD.h"
#include "bigint.h"

void SUBAbB( word* A, word* B, word* C, word* b );
void SUBC( bigint** A, bigint** B, bigint** C );
void SUB( bigint** A, bigint** B, bigint** C );

#endif
