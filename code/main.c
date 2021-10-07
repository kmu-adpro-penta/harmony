#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
int main(){
	bigint** bi=NULL;
	bi = malloc(sizeof(bigint*));
	word w[3] = {0x4343,0x5678, 0x1234};

	//printf("start\n");
	fflush(stdout);
	bi_set_by_array(bi, NON_NEGATIVE, w, 12);
	bi_show_hex(*bi);
	bi_delete(bi);

	return 0;
}