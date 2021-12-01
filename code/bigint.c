#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
* all of a value initialize
*/
void array_init(word* a, int wordlen) {
	for (int i = 0; i < wordlen; i++)
		a[i] = 0x0;
}
/**
 * @brief delete bigint x
 *
 * @param x bigint you want to delete
 */
void bi_delete(bigint** x) {
	if (*x == NULL)
		return;

#ifdef ZERORIZE 
	array_init((*x)->a, (*x)->wordlen);
#endif
	free((*x)->a);
	free((*x));
	*x = NULL;
}

/**
 * @brief make new bigint
 *
 * @param x bigint you want to make
 * @param wordlen word length of bigint
 */
void bi_new(bigint** x, int wordlen) {
	if (*x != NULL)
		bi_delete(x);
	*x = (bigint*)malloc(sizeof(bigint));
	(*x)->sign = NON_NEGATIVE;
	(*x)->wordlen = wordlen;
	(*x)->a = (word*)calloc(wordlen, sizeof(word));
}

/**
 * @brief set bigint by array
 *
 * @param x bigint you want to set
 * @param sign NEGATIVE OR NONNEGATIVE
 * @param a word array
 * @param wordlen word length of a
 */
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen) {
	if (*x == NULL) {
		bi_new(x, wordlen);
	}
	(*x)->sign = sign;
	(*x)->wordlen = wordlen;
	for (int i = 0; i < wordlen; i++) {
		(*x)->a[i] = a[i];
	}
}


/**
 * @brief character digit [0-9a-fA-F] to int
 *
 * @param c character you want to change to int
 * @return int
 * 	if you input other character, return -1
 */
int chartohex(char c) {
	unsigned int n = (unsigned int)c - 0x30;
	//case of [0-9]
	if (n < 10)
		return (int)n;
	n -= 0x11;
	//case of [A-F]
	if (n < 6)
		return (int)n + 10;
	n -= 0x20;
	//case of [a-f]
	if (n < 6)
		return (int)n + 10;
	return -1;
}

/**
 * @brief return a / b and ceil it ex) cdevide(7, 4) == 2
 *
 * @param a devidend
 * @param b divisor
 * @return int quotient
 */
int cdevide(int a, int b) {
	int answer = a / b;
	if (answer * b != a)
		return answer + 1;
	else
		return answer;
}

//string to bigint
void bi_set_by_string(bigint** x, int sign, char* str, int base) {
	int i;
	//int len;
	byte* w = NULL;
	//int n;

	if (*x == NULL) {
		bi_new(x, cdevide(base, sizeof(word) * 2));
	}

	(*x)->sign = sign;

	//base to wordlen
	(*x)->wordlen = cdevide(base, sizeof(word) * 2);

	//make new array use str
	int malsiz = sizeof(word) * (*x)->wordlen;
	w = malloc(malsiz);
	i = base - 1;
	while (i > 0) {
		w[(base - 1 - i) / 2] = chartohex(str[i]) | chartohex(str[i - 1]) << 4;
		i -= 2;
	}
	if (base & 1)
		w[base / 2] = chartohex(str[0]);

	for (i = (base + 1) / 2; i < malsiz; i++)
		w[i] = 0x0;
	(*x)->a = (word*)w;
}

/**
 * @brief stdout bigint x hexadecade
 *
 * @param x bigint
 */
void bi_show_hex(bigint* x) {
	if (x == NULL) { fprintf(stdout, "0x0"); return; }
	int i;
	if (bi_get_sign(x) == NEGATIVE)
		fprintf(stdout, "-");
	fprintf(stdout, "0x");
	for (i = x->wordlen - 1; i >= 0; i--) {
#ifdef BIT64
		fprintf(stdout, "%016llx", x->a[i]);
#endif
#ifdef BIT32
		fprintf(stdout, "%08x", x->a[i]);
#endif
#ifdef BIT16
		fprintf(stdout, "%04x", x->a[i]);
#endif
#ifdef BIT8
		fprintf(stdout, "%02x", x->a[i]);
#endif
	}
}

/**
 * @brief stdout bigint x binary
 *
 * @param x bigint
 */
void bi_show_bin(bigint* x) {
	if (x == NULL) { fprintf(stdout, "0b0"); return; }
	int i, j;

	if (bi_get_sign(x) == NEGATIVE)
		fprintf(stdout, "-");
	fprintf(stdout, "0b");

	for (i = x->wordlen - 1; i >= 0; i--) {
		int temp = x->a[i];
		for (j = sizeof(word) * BYTE - 1; j >= 0; j--) {
			fprintf(stdout, "%x", (temp >> j) & 1);
		}
	}
}

/**
 * @brief make x memory fit to it
 * 	ex) 000012345678 -> 12345678
 *
 * @param x target bigint
 */
void bi_refine(bigint* x) {
	if (x == NULL)
		return;

	int new_wordlen = x->wordlen;
	while (new_wordlen > 1) {
		if (x->a[new_wordlen - 1] != 0)
			break;
		new_wordlen--;
	}
	if (x->wordlen != new_wordlen) {
		x->wordlen = new_wordlen;
		x->a = (word*)realloc(x->a, sizeof(word) * new_wordlen);
	}

	if ((x->wordlen == 1) && (x->a[0] == 0x0))
		x->sign = NON_NEGATIVE;
}


/**
 * @brief copy array
 *
 * @param dst
 * @param arr
 * @param wordlen
 */
void array_copy(word* dst, word* arr, int wordlen) {
	memcpy(dst, arr, wordlen * sizeof(word));
}

/**
 * @brief make bigint y to be equal with bigint x
 *
 * @param y bigint** same amount with bigint x
 * @param x bigint* you want to copy
 */
void bi_assign(bigint** y, bigint* x) {
	if (*y != NULL)
		bi_delete(y);
	bi_new(y, x->wordlen);
	(*y)->sign = x->sign;
	array_copy((*y)->a, x->a, x->wordlen);
}


//need to change, low security
void array_rand(word* dst, int wordlen) {
	byte* p = (byte*)dst;
	int i;
	for (i = 0; i < wordlen * sizeof(word); i++) {
		*p = rand() & 0xff;
		p++;
	}
}
//create random bigint
void bi_gen_rand(bigint** x, int sign, int wordlen) {
	if (*x != NULL)
		bi_delete(x);
	bi_new(x, wordlen);
	(*x)->sign = sign;
	array_rand((*x)->a, wordlen);

	bi_refine(*x);
}

//return wordlen
int bi_get_wordlen(bigint* x) {
	if (x == NULL) return 0;
	return x->wordlen;
}

//return wordlen * BYTE(8) * sizeof(word)
int bi_get_bitlen(bigint* x) {
	if (x == NULL) return 0;
	int bitlen = x->wordlen * BYTE * sizeof(word);
	for (int i = x->wordlen - 1; i >= 0; i--) {
		if (x->a[i] == 0)
			bitlen -= BYTE * sizeof(word);
		else {
			for (int j = BYTE * sizeof(word) - 1; j >= 0; j--) {
				if (x->a[i] >> j & 0x1)
					break;
				bitlen--;
			}
			break;
		}
	}
	return bitlen;
}

// what do you want to get??
int bi_get_ibit(bigint* x, int i) {
	return (x->a[i / (sizeof(word) * BYTE)] >> i % (sizeof(word) * BYTE)) & 0x1;
}

//return sign
int bi_get_sign(bigint* x) {
	if (x == NULL) return NON_NEGATIVE;
	return x->sign;
}
//return !sign
int bi_get_flipsign(bigint* x) {
	if (x == NULL) return NEGATIVE;
	return x->sign ? NON_NEGATIVE : NEGATIVE;
}


//create bigint 1
void bi_set_one(bigint** x) {
	if (*x != NULL)
		bi_delete(x);
	bi_new(x, 1);
	(*x)->sign = NON_NEGATIVE;
	*((*x)->a) = 0x1;
}


//create bigint 0
void bi_set_zero(bigint** x) {
	if (*x != NULL)
		bi_delete(x);
	bi_new(x, 1);
	(*x)->sign = NON_NEGATIVE;
	*((*x)->a) = 0x0;
}
//if bigint is 0, return 1 else 0
int bi_is_zero(bigint* x) {
	int i;
	if ((x->sign == NEGATIVE) | (x->a[0] != 0))
		return FALSE;

	for (i = x->wordlen - 1; i > 0; i--) {
		if (x->a[i])
			return FALSE;
	}
	return TRUE;
}
//if bigint is 1, return 1 else 0
int bi_is_one(bigint* x) {
	int i;
	if ((x->sign == NEGATIVE) | (x->a[0] != 1))
		return FALSE;

	for (i = x->wordlen - 1; i > 0; i--) {
		if (x->a[i])
			return FALSE;
	}
	return TRUE;
}

//abs compare
int bi_compare_abs(bigint* x, bigint* y) {
	int i;
	if (x->wordlen > y->wordlen)
		return GREATER;
	else if (x->wordlen < y->wordlen)
		return LESS;

	for (i = x->wordlen - 1; i >= 0; i--) {
		if (x->a[i] > y->a[i])
			return GREATER;
		else if (x->a[i] < y->a[i])
			return LESS;
	}
	return EQUAL;
}
//compare 

int bi_compare(bigint* x, bigint* y) {
	if ((x->sign == NON_NEGATIVE) & (y->sign == NEGATIVE))
		return GREATER;
	if ((x->sign == NEGATIVE) & (y->sign == NON_NEGATIVE))
		return LESS;

	int com_abs = bi_compare_abs(x, y);
	if (x->sign == NON_NEGATIVE)
		return com_abs;
	else
		return com_abs * (-1);
}
/*
* bigint right shift
*/
void bi_rshift(bigint** x, int r) {
	int k, re, i;
	// case: r > wn
	if (r > (*x)->wordlen * sizeof(word) * BYTE)
		bi_set_zero(x);
	// case: r = wk
	else {
		k = r / (sizeof(word) * BYTE);
		re = r & (sizeof(word) * BYTE - 1);
		memmove((*x)->a, &((*x)->a[k]), (*x)->wordlen * sizeof(word) - k);
		memset(&((*x)->a[(*x)->wordlen - k]), 0, k * sizeof(word));
		bi_refine(*x);

		// case: r = wk+r'
		if (re) {
			for (i = 0; i < (*x)->wordlen - 1; i++) {
				(*x)->a[i] = (*x)->a[i + 1] << (sizeof(word) * BYTE - re) | (*x)->a[i] >> re;
				//printf("%x ",(*x)->a[i]);
			}
			(*x)->a[(*x)->wordlen - 1] = (*x)->a[(*x)->wordlen - 1] >> re;
		}

	}
}
/*
* bigint left shift
*/
void bi_lshift(bigint** x, int r) {
	int k, re, i, len;
	k = r / (sizeof(word) * BYTE);
	re = r & (sizeof(word) * BYTE - 1);
	len = (*x)->wordlen;
	//bi_show_hex(*x);
	bi_realloc(x, k + 1);
	memmove(&((*x)->a[k]), (*x)->a, len * sizeof(word));
	memset((*x)->a, 0, k * sizeof(word));

	if (re) {
		//word b = (*x)->a[0];
		(*x)->a[len + k] = (*x)->a[len + k - 1] >> (sizeof(word) * BYTE - re);
		for (i = len - 1; i > 0; i--) {
			(*x)->a[i + k] = (*x)->a[i + k] << re | (*x)->a[i + k - 1] >> (sizeof(word) * BYTE - re);
		}
		(*x)->a[k] = (*x)->a[k] << re;
	}
	bi_refine(*x);

}
/*
* bicint realloc
*/
void bi_realloc(bigint** x, int i) {
	int n;
	word* w;
	w = (word*)malloc(((*x)->wordlen + i) * sizeof(word));
	memcpy(w, (*x)->a, (*x)->wordlen * sizeof(word));
	for (n = 0; n < i; n++) {
		w[(*x)->wordlen + n] = 0;
	}
	(*x)->wordlen += i;
	free((*x)->a);
	(*x)->a = w;
}

void bi_mod(bigint* x, int r, bigint** n) {
	if (x == NULL) {
		bi_set_zero(n);
		return;
	}
	if (x->wordlen <= r) {
		bi_assign(n, x);
		return;
	}
	bi_new(n, r);
	(*n)->sign = bi_get_sign(x);
	for (int i = 0; i < r; i++) {
		(*n)->a[i] = x->a[i];
	}
}
void bi_max_number(word* Q) {
#ifdef BIT8
	* Q = 255;
#endif
#ifdef BIT16
	* Q = 65535;
#endif
#ifdef BIT32
	* Q = 4294967295;
#endif
#ifdef BIT64
	* Q = 18446744073709551615;
#endif
}


//void bi_lshift(bigint** x, int r) {
//	int k, re, i, len;
//	bigint* w = NULL;
//	word b1, b0;
//	k = r/(sizeof(word)*BYTE);
//	re = r & (sizeof(word)*BYTE - 1);
//	len = (*x)->wordlen;
//	bi_new(&w, (*x)->wordlen + k + 1);
//	w->sign = (*x)->sign;
//	
//	for (i = (*x)->wordlen; i > 0; i--)
//		w->a[i + k - 1] = (*x)->a[i - 1];
//	
//	if(re) {
//		b0 = w->a[k - 1] >> re;
//		for (i = 0; i < (*x)->wordlen; i++) {
//			b1 = w->a[k + i] >> re;
//			w->a[k - 1 + i] << re;
//			w->a[k + i] =  (w->a[k + i] << re) | b0;
//			b0 = b1;
//		}
//	}
//	bi_refine(w);
//	bi_assign(x, w);
//	bi_delete(&w);
//	
//}
