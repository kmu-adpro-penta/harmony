#include "bigint.h"
#include "ADD.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#include "MOD.h"
#define MAIN

void modt() {
	for(int i=0; i<100000; i++)
	{

		bigint* a =NULL;
		bigint* b= NULL;
		bi_gen_rand(&a, NON_NEGATIVE, 6);
		bi_gen_rand(&b, NON_NEGATIVE, 6);
		/*
		bi_show_hex(a);
		printf("\n");
		bi_show_hex(b);
		printf("\n");

		printf("ltr : ");
		bigint* c= NULL;
		ex_ltr_mul(a, b, &c);
		bi_show_hex(c);
		printf("\n");

		printf("rtl : ");
		bigint* d = NULL;
		ex_rtl_mul(a, b, &d);
		bi_show_hex(d);
		printf("\n");

		printf("mul : ");
		bigint* e = NULL;
		SchoolbookMUL(a, b, &e);
		bi_show_hex(e);
		printf("\n");

		bi_delete(&c);
		bi_delete(&d);
		bi_delete(&e);
		printf("end\n");
		*/
		bigint* c= NULL;
		ex_ltr_mul(a, b, &c);
		bigint* d = NULL;
		ex_rtl_mul(a, b, &d);
		bigint* e = NULL;
		SchoolbookMUL(a, b, &e);
		if((bi_compare(c, d) != 0 ) || (bi_compare(d, e) != 0)) {
			printf("%d\n", i);
			bi_show_hex(a);
			printf("\n");
			bi_show_hex(b);
			printf("\n");

			bi_show_hex(c);
			printf("\n");
			bi_show_hex(d);
			printf("\n");
			bi_show_hex(e);
			printf("\n");
			break;
		}
		bi_delete(&c);
		bi_delete(&d);
		bi_delete(&e);
			printf("%d\n", i);
	}
	printf("ok");
}

void mont() {
	bigint* N=NULL;
	bi_gen_rand(&N, NON_NEGATIVE, 10);
	bi_lshift(&N, 1);
	bigint* R=NULL;
	bi_set_one(&R);
	ADD(N, R, &N);

	bi_lshift(&R, bi_get_wordlen(N)*sizeof(word)*BYTE);
	bi_show_hex(N);
	printf("\n");
	bi_show_hex(R);
	bigint* NN=NULL;
	invN(N, R, &NN);
	bi_show_hex(NN);
}


int main() {
	mont();
	return 0;
}





void kara() {
	
	//int i = 0;
	//for (i; i < 10000; i++) {
	srand(time(NULL));
	bigint* A = NULL;
	bi_gen_rand(&A, NON_NEGATIVE, 3);
	bigint* B = NULL;
	bi_gen_rand(&B, NON_NEGATIVE, 3);
	bigint* C = NULL;
	bigint* D = NULL;
	printf("A = ");
	bi_show_hex(A);
	printf("\nB = ");
	bi_show_hex(B);
	printf("\n");
	SchoolbookMUL(A, B, &D);
	printf("D =");
	bi_show_hex(D);
	printf("\n");

	KaratsubaMUL(2, A, B, &C);
	printf("C = ");
	bi_show_hex(C);
	printf("\n");
	printf("A = ");
	bi_show_hex(A);
	printf("\nB = ");
	bi_show_hex(B);
	printf("\n");

	//printf("\nAA = ");

//bigint* AA = NULL;
//ADD(B, C, &AA);

//bi_show_hex(AA);
//printf("\n");

//if (bi_compare(A, AA) != 0) {

	//	//bi_realloc(&A, 4);
	//	printf("you die%d", i);
	//	printf("\n");
	//	return 0;
	//}
	bi_delete(&A);
	bi_delete(&B);
	bi_delete(&C);
	//bi_delete(&AA);
//}
	printf("hi");
}

void toy2() {
	for (int i = 0; i < 100; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 7);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 3);

		bigint* Q = NULL;
		bigint* R = NULL;

		printf("\n");
		printf("print(");
		bi_show_hex(A);
		printf(" // ");
		bi_show_hex(B);
		DIV(A, B, &Q, &R);
		printf(" == ");
		bi_show_hex(Q);
		printf(")");

		printf("\n");
		printf("print(");
		bi_show_hex(A);
		printf(" %% ");
		bi_show_hex(B);
		printf(" == ");
		bi_show_hex(R);
		printf(")");


	}

}

void toy3() {
	bigint* C = NULL;
	bigint* D = NULL;
	bigint** A = NULL;
	bi_gen_rand(&C, NON_NEGATIVE, 3);


	bi_assign(&D, C);
	bi_assign(A, C);


}
/*
void toy4() {

	PyObject* pName, * pModule, * pFunc, * pValue;

	Py_Initialize();

	pName = PyUnicode_FromString("Big_int_test"); // testFile.py�� PyObject�� �����Ѵ�.

	pModule = PyImport_Import(pName); // ������ PyObject pName�� import�Ѵ�.

	pFunc = PyObject_GetAttrString(pModule,"test_func"); // ������ �Լ��� test_func�� PyObject�� �����Ѵ�.

	for (int i = 0; i < 100; i++) {
		bigint* A = NULL;
		bi_gen_rand(&A, NON_NEGATIVE, 7);
		bigint* B = NULL;
		bi_gen_rand(&B, NON_NEGATIVE, 3);

		bigint* R = NULL;
		pValue = PyObject_CallObject(pFunc, NULL); // pFunc�� �Ű������� �����ؼ� �����Ѵ�. 

	}
	Py_Finalize();

}
*/
int main() {
	srand(time(NULL));
	clock_t start, end;
	start = clock();
	toy1();
	end = clock();
	printf("\nruntime is %fms", (double)(end - start) / repeat);
	return 0;
}
