#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>



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