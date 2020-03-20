#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){

	int input = atoi(argv[1]);

	char** name;
	name = (char**)malloc(sizeof(char*) * input);

	printf("enter %d names:\n", input);

	for (int i = 0; i < input; i++){
		name[i] = (char*)malloc(sizeof(char) * 35);
		scanf("%s", name[i]);
	}	

	printf("the names you entered:\n");
	
	for (int j = 0; j < input; j++){
		printf("%s\n", name[j]);
		free(name[j]);
	}
	free(name);
}
