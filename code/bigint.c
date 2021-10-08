#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define GREATER 1
#define EQUAL 0
#define LESS -1

//delete bigint
void bi_delete(bigint** x) {
	if(*x == NULL)
		return; 

#ifdef ZERORIZE 
	array_init((*x)->a, (*x)->wordlen);
#endif

	free((*x)->a);
	free((*x));
	*x = NULL;
}

//new bigint
void bi_new(bigint** x, int wordlen) {
	if(*x != NULL)	
		bi_delete(x);

	*x = (bigint*)malloc(sizeof(bigint));
	(*x)->sign = NON_NEGATIVE;
	(*x)->wordlen = wordlen;
	(*x)->a = (word*)calloc(wordlen, sizeof(word));
}

//set bigint by array
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen) {
	(*x)->sign = sign;
	(*x)->wordlen = wordlen;
	(*x)->a = a;
}

int chartohex(char c) {
	unsigned int n = (unsigned int)c - 0x30;
	if (n<10)
		return (int)n;
	n -= 0x11;
	if (n<6)
		return (int)n+10;
	n -= 0x20;
	if (n<6)
		return (int)n+10;
	return -1;
}
int cdevide(int a, int b) {
	int answer = a / b;
	if(answer*b != a) 
		return answer+1;
	else
		return answer;
}
/*
void bi_set_by_string(bigint** x, int sign, char* str, int base {
	int i;
	int len;
	char* w= NULL;
	int n;

	(*x)->sign = sign;

	//base to wordlen
	(*x)->wordlen = cdevide(base, sizeof(word));
	
	//make new array use str
	int malsiz = sizeof(word)*(*x)->wordlen;
	w = malloc(malsiz);
	for (i=0; i<malsiz-base; i++) {
		w[malsiz-1-i] = 0;	
	}
	for(i=0; i < base; i++) {
		w[base-1-i] = chartohex(str[i]);
	}
	(*x)-> = strtoarr(str);
}*/

//print bigint 16
void bi_show_hex(bigint* x) {
	for(int i = x->wordlen-1; i >= 0; i--)
		fprintf(stdout, "%x", x->a[i]);
}

void bi_refine(bigint* x) {
	if(x == NULL)
		return;
	
	int new_wordlen = x->wordlen;
	while(new_wordlen > 1) {
		if(x->a[new_wordlen - 1] != 0)
			break;
		new_wordlen--;
	}
	if (x->wordlen != new_wordlen) {
		x->wordlen = new_wordlen;
		x->a = (word*)realloc(x->a, sizeof(word)*new_wordlen);
	}

	if((x->wordlen == 1) && (x->a[0] == 0x0))
		x->sign = NON_NEGATIVE;
}

void bi_assign(bigint** y, bigint *x) {
	if(*y != NULL)
		bi_delete(y);

	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	//array_copy((*y)->a, x->a, x->wordlen);
}


void bi_gen_rand(bigint**x, int sign, int wordlen) {
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}
//need to change, low security
void array_rand(word* dst, int wordlen) {
	byte* p = (byte*)dst;
	int cnt = wordlen * sizeof(word);
	while(cnt > 0) {
		*p = rand() & 0xff;
		p++;
		cnt--;
	}
}

//create bigint 1
void bi_set_one(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NON_NEGATIVE;
	(*x)->a[0] = 0x1;
}
//create bigint 0
void bi_set_zero(bigint** x) {
	bi_new(x, 1);
	(*x)->sign = NON_NEGATIVE;
	(*x)->a[0] = 0x0;
}
//if bigint is 0, return 1 else 0
int bi_is_zero(bigint* x) {
	int i;
	if(x->sign == NEGATIVE | x->a[0] != 0)
		return FALSE;
	
	for(i=x->wordlen; i>0; i--) {
		if(x->a[i])
			return FALSE;
	}
	return TRUE;
}
//if bigint is 1, return 1 else 0
int bi_is_one(bigint* x) {
	int i;
	if(x->sign == NEGATIVE | x->a[0] != 0)
		return FALSE;
	
	for(i=x->wordlen; i>0; i--) {
		if(x->a[i])
			return FALSE;
	}
	return TRUE;
}

//abs compare
int bi_compare_abs(bigint* x, bigint* y) {
	int i;
	if(x->wordlen > y->wordlen)
		return GREATER;
	else if(x->wordlen < y->wordlen)
		return LESS;
	
	for(i=x->wordlen-1; i>=0; i--) {
		if(x->a[i] > y->a[i])
			return GREATER;
		else if (x->a[i] < y->a[i])
			return LESS;
	}
	return EQUAL;
}
//compare 
int bi_compare(bigint* x, bigint* y) {
	if(x->sign==NON_NEGATIVE & y->sign==NEGATIVE)
		return GREATER;
	if(x->sign==NEGATIVE & y->sign==NON_NEGATIVE)
		return LESS;
	
	int com_abs = bi_compare_abs(x,y);
	if(x->sign == NON_NEGATIVE)
		return com_abs;
	else
		return com_abs*(-1);
}