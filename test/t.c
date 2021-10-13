#include <stdio.h>
#include <string.h>
int main() {
	char w[] = "qwerasdfzxcv";
	char* k;
	memcpy(k, &w[3], 9);
	printf("%s\n", k);
	printf("%d\n", sizeof(k));
}