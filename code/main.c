#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

#define MAIN
int main(){
	bigint* bi=NULL;
	bi_new(&bi, 2);
	word w[2] = {0x5678, 0x1234};

	printf("start\n");
	//bi_set_by_array(&bi, NON_NEGATIVE, w, 2);
	bi_set_by_string(&bi, NON_NEGATIVE, "1234abcd", 8);
	printf("worlen : %d\n", bi_get_wordlen(bi));
	bi_show_hex(bi);
	printf("\n");
	bi_show_bin(bi);
	bi_delete(&bi);

	return 0;
}