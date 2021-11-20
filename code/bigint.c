#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define GREATER 1
#define EQUAL 0
#define LESS -1
#define BYTE 8

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

//set bigint by array error
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen) {
	(*x)->sign = sign;
	(*x)->wordlen = wordlen;
	free((*x)->a);
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

//string to bigint
void bi_set_by_string(bigint** x, int sign, char* str, int base) {
	int i;
	int len;
	byte* w= NULL;
	int n;

	(*x)->sign = sign;

	//base to wordlen
	(*x)->wordlen = cdevide(base, sizeof(word)*2);
	
	//make new array use str
	int malsiz = sizeof(word)*(*x)->wordlen;
	w = malloc(malsiz);
	i = base-1;
	while(i>0) {
		w[(base-1-i)/2] = chartohex(str[i]) | chartohex(str[i-1])<<4;
		i -= 2;
	}
	if(base&1)
		w[base/2] = chartohex(str[0]);
	
	for(i=(base+1)/2; i<malsiz; i++)
		w[i] = 0x0;
	(*x)->a = (word*)w;
}

//print bigint 16
void bi_show_hex(bigint* x) {
	int i;
	for(i = x->wordlen-1; i >= 0; i--)
		fprintf(stdout, "%04x", x->a[i]);
}
void bi_show_bin(bigint* x) {
	int i, j;
	for(i = x->wordlen-1; i >= 0; i--) {
		int temp = x->a[i];
		for(j = sizeof(word)*BYTE-1; j>=0; j--) {
			fprintf(stdout, "%x", (temp>>j)&1);
		}
	}
}

//make memory fit word
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


//array copy, need to valid check
void array_copy(word* dst, word* arr,int wordlen) {
	memcpy(dst, arr, wordlen*sizeof(word)*BYTE);
}

//assign y <- x
void bi_assign(bigint** y, bigint *x) {
	if(*y != NULL)
		bi_delete(y);

	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	array_copy((*y)->a, x->a, x->wordlen);
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
//create random bigint
void bi_gen_rand(bigint**x, int sign, int wordlen) {
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}

//return wordlen
int bi_get_wordlen(bigint* x) {
	return x->wordlen;
}

//return wordlen * BYTE(8) * sizeof(word)
int bi_get_bitlen(bigint* x) {
	return x->wordlen*BYTE*sizeof(word);
}

// what do you want to get??
int bi_get_ibit(bigint* x, int i) {
	x->a[i>>(sizeof(word)*BYTE)] >> ((1<<(sizeof(word)*BYTE) - 1) & i);
}

//return sign
int bi_get_sign(bigint* x) {
	return x->sign;
}
//return !sign
int bi_get_flipsign(bigint* x) {
	return x->sign ? NON_NEGATIVE : NEGATIVE;
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

void bi_rshift(bigint** x, int r) {
	int k, re, i;
	// case: r > wn
	if (r > (*x)->wordlen * sizeof(word) * BYTE)
		bi_set_zero(x);
	// case: r = wk
	else {
		k = r/(sizeof(word)*BYTE);
		re = r & (sizeof(word)*BYTE - 1);
		memmove((*x)->a, &((*x)->a[k]), (*x)->wordlen*sizeof(word)-k);
		memset(&((*x)->a[(*x)->wordlen - k]), 0, k*sizeof(word));
		bi_refine(*x);

		// case: r = wk+r'
		if(re) {
			for(i=0; i<(*x)->wordlen-1; i++) {
				(*x)->a[i] = (*x)->a[i+1] << (sizeof(word)*BYTE-re) | (*x)->a[i] >> re;
				//printf("%x ",(*x)->a[i]);
			}
			(*x)->a[(*x)->wordlen - 1] = (*x)->a[(*x)->wordlen - 1] >> re;
		}

	}
}

void bi_lshift(bigint** x, int r) {
	int k, re, i, len;
	word b;
	k = r/(sizeof(word)*BYTE);
	re = r & (sizeof(word)*BYTE - 1);
	len = (*x)->wordlen;

	bi_realloc(x, k+1);
	memmove(&((*x)->a[k]), (*x)->a, len*sizeof(word));
	memset((*x)->a, 0, k*sizeof(word));
	
	if(re) {
		b = (*x)->a[0];
		(*x)->a[len + k] = (*x)->a[len + k - 1] >> (sizeof(word) * BYTE - re);
		for(i=len-1; i>0; i--) {
			(*x)->a[i + k] = (*x)->a[i + k] << re | (*x)->a[i + k - 1] >> (sizeof(word) * BYTE - re);
		}
		(*x)->a[k] = (*x)->a[k] << re;
	}
	bi_refine(*x);
	
}

void bi_realloc(bigint** x, int i) {
	int n;
	realloc((*x)->a, ((*x)->wordlen + i)*sizeof(word));
	for(n=0; n<i; n++) {
		(*x)->a[(*x)->wordlen + n] = 0;
	}
	(*x)->wordlen+= i;

}
