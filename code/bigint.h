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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned short word;
typedef unsigned char byte;

typedef struct {
	int sign;
	int wordlen;
	word* a;
} bigint;

void bi_delete(bigint** x);
void bi_new(bigint** x, int wordlen);

void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);
void bi_set_by_string(bigint** x, int sign, char*str, int base);

void bi_show_hex(bigint* x);
void bi_show_dec(bigint* x);//too hard
void bi_show_bin(bigint* x);

void bi_refine(bigint* x);

void bi_assign(bigint** y, bigint* x);

void bi_gen_rand(bigint** x, int sign, int wordlen);//fix

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
#endif