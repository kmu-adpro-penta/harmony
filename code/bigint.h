#ifndef __BIGINT_H__
#define __BIGINT_H__

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define NON_NEGATIVE 0
#define NEGATIVE 1
#define FALSE 0
#define TRUE 1
#define GREATER 1
#define EQUAL 0
#define LESS -1
#define BYTE 8
#define ZERORIZE
#define BIT8
#define LoopCTR 1000
#define flag 2
#define MAX_RAND 1000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef BIT8
#ifndef BIT16
#ifndef BIT32
#ifndef BIT64
#define BIT8
#endif
#endif
#endif
#endif



#ifdef BIT64
typedef unsigned long long word;
#endif
#ifdef BIT32
typedef unsigned int word;
#endif
#ifdef BIT8
typedef unsigned char word;
#endif
#ifdef BIT16
typedef unsigned short word;
#endif


typedef unsigned char byte;

typedef struct {
	int sign;
	int wordlen;
	word* a;
} bigint;

void array_init(word* a, int wordlen);

void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);

void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
void bi_set_by_string(bigint** x, int sign, char*str);

void bi_show_hex(bigint* x);
void bi_show_dec(bigint* x);//too hard
void bi_show_bin(bigint* x);

void bi_refine(bigint* x);

void bi_assign(bigint** y, bigint* x);

void bi_gen_rand(bigint** x, int sign, int wordlen);
void bi_gen_full_rand(bigint**x);

int bi_get_wordlen(bigint* x);
int bi_get_bitlen(bigint* x);

int bi_get_ibit(bigint* x, int i);//fix
int bi_get_sign(bigint* x);
int bi_get_flipsign(bigint* x);

void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int bi_is_zero(bigint* x);
int bi_is_one(bigint* x);

int bi_compare_abs(bigint* x, bigint* y);
int bi_compare(bigint* x, bigint* y);

void bi_rshift(bigint** x, int r);
void bi_lshift(bigint** x, int l);//yet

void bi_realloc(bigint** x, int i);

void bi_mod(bigint*x, int r, bigint** n);
void bi_max_number(word* Q);

#endif