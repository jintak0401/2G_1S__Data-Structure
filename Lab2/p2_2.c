#include <stdio.h>


int main(){
	char name[32];

	printf("enter your name:\n");
	scanf("%[^\n]", name);
	printf("your name is %s\n", name);

}
