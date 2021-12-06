#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
void multest();


void test() {
	bigint* a = NULL;
	bigint* b = NULL;
	bi_set_by_string(&a, NON_NEGATIVE, "123456789");
	bi_set_by_string(&b, NON_NEGATIVE, "abcdef");

	printf("a = ");
	bi_show_hex(a);
	printf("\nb = ");
	bi_show_hex(b);

	bigint* add = NULL;
	bigint* sub = NULL;
	bigint* mul = NULL;
	bigint* div = NULL;
	bigint* r = NULL;
	ADD(a, b, &add);
	SUB(a, b, &sub);
	MUL(a, b, &mul);
	DIV(a, b, &div, &r);

	printf("\na + b = ");
	bi_show_hex(add);
	printf("\na - b = ");
	bi_show_hex(sub);
	printf("\na * b = ");
	bi_show_hex(mul);
	printf("\na // b = ");
	bi_show_hex(div);
	printf("\na %% b = ");
	bi_show_hex(r);

	bi_delete(&a);
	bi_delete(&b);
	bi_delete(&add);
	bi_delete(&sub);
	bi_delete(&mul);
	bi_delete(&div);
	bi_delete(&r);
}


int main() {
	multest();
	return 0;
}



void multest() {
	for(int i=0; i<1000; i++)
	{
		bigint* a = NULL;
		bigint* b = NULL;
		bi_gen_rand(&a, NON_NEGATIVE, 50);
		bi_gen_rand(&b, NON_NEGATIVE, 10);
		printf("a = ");
		bi_show_hex(b);
		printf("\nb = ");
		bi_show_hex(a);
		printf("\n");
		bigint* c = NULL;
		bigint* d = NULL;
		DIV(a, b, &c, &d);
		printf("c = ");
		bi_show_hex(c);
		printf("\nd = ");	
		bi_show_hex(d);
		printf("\n");
		printf("\nif a//b == c and a%%b == d:\n\tprint('ok')\nelse:\n\tprint('error')\n");
		bi_delete(&a);
		bi_delete(&b);
		bi_delete(&c);
	}
}

