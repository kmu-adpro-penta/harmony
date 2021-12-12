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
	for(int i=0; i<10; i++)
	{
		bigint* a = NULL;
		bigint* b = NULL;
		bi_gen_rand(&a, NON_NEGATIVE, 1000);
		bi_gen_rand(&b, NON_NEGATIVE, 1000);
		printf("a = ");
		bi_show_hex(a);
		printf("\nb = ");
		bi_show_hex(b);
		printf("\n");
		bigint* c = NULL;
		KaratsubaMUL(3, a, b, &c);
		printf("c = ");
		bi_show_hex(c);
		printf("\n");
		printf("\nif a*b == c:\n\tprint('ok')\nelse:\n\tprint('error')\n");
		bi_delete(&a);
		bi_delete(&b);
		bi_delete(&c);
	}
}
