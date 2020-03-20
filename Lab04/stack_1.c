#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int x);
int IsFull(Stack* s);
int top(Stack* s);


void DeleteStack(Stack* s);

void main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1], "r");

	Stack* stack;
	char input_str[101];
	int max, i = 0, a, b, result;

	fgets(input_str, 101, fi);
	max = 10;
	stack = CreateStack(max);


	for (i = 0; i < strlen(input_str) && input_str[i] != '#'; i++){
		Push(stack, input_str[i] - '0');

	}


	fclose(fi);
	DeleteStack(stack);
}

Stack* CreateStack(int max){
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (s == NULL){
		printf("Out of memory!!!\n");
		return NULL;
	}
	s -> key = (int*)malloc(sizeof(int) * max);
	s -> top = -1;
	s -> max_stack_size = max;
	return s;
}

int IsFull(Stack* s){
	if ((s -> top) + 1 == s -> max_stack_size){
		printf("Stack is full\n");
		return 1;
	}
	return 0;
}

void Push(Stack* s, int x){
	if (IsFull(s)){
		printf("You cannot input in stack\n");
		return;
	}	
	s -> key[++(s -> top)] = x;

	printf("%d inserted\n", x);
}

void DeleteStack(Stack* s){
	free(s -> key);
	free(s);
}

int top(Stack* s){
	int tmp = s -> key[s -> top];
	printf("top : %d\n", tmp);	
	return tmp;
}
