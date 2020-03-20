#include <stdio.h>

void swap(int* a, int* b);

int main(){
	int a, b;
	printf("enter 2 integers\n");
	scanf("%d%d", &a, &b);
	printf("you entered\n%d, %d\n", a, b);
	swap(&a, &b);
	printf("after swapping\n%d, %d\n", a, b);
}


void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
