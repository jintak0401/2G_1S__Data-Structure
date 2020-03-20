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

int Pop(Stack* s);
int IsEmpty(Stack* s);
int Postfix(Stack* s, char input_str);  


void main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1], "r");

	Stack* stack;
	char input_str[101];
	int max, i = 0, a, b, result;

	fgets(input_str, 101, fi);
	max = 10;
	stack = CreateStack(max);

	printf("Top numbers : ");

	for (i = 0; i < strlen(input_str) && input_str[i] != '#'; i++){
		

		result = Postfix(stack, input_str[i]);
	}

	printf("\nevaluation result : %d\n", result);

	fclose(fi);
	DeleteStack(stack);
}

int Postfix(Stack* s, char input_char){
	int a, b;
	int result;
	switch(input_char){
		case '+':
			b = Pop(s);
			a = Pop(s);
			result = a + b;	
			Push(s, result);
			break;
		case '-':
			b = Pop(s);
			a = Pop(s);
			result = a - b;	
			Push(s, result);

			break;
		case '*':
			b = Pop(s);
			a = Pop(s);
			result = a * b;	
			Push(s, result);

			break;
		case '/':
			b = Pop(s);
			a = Pop(s);
			result = a / b;	
			Push(s, result);

			break;
		case '%':
			b = Pop(s);
			a = Pop(s);
			result = a % b;	
			Push(s, result);

			break;
		default:
			result = input_char - '0';
			Push(s, result);
			break;
	}
	printf("%d ", top(s));
	return result;
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
		return 1;
	}
	return 0;
}

void Push(Stack* s, int x){
	if (IsFull(s)){
		printf("Stack is full\n");
		printf("You cannot input in stack\n");
		return;
	}	
	s -> key[++(s -> top)] = x;

}

void DeleteStack(Stack* s){
	free(s -> key);
	free(s);
}

int Pop(Stack* s){
	if(IsEmpty(s)){
		printf("Stack is already emtpy\n");
		printf("You cannot Pop out\n");
		return -1;
	}
	return s -> key[(s -> top)--];
}
int IsEmpty(Stack* s){
	if (s -> top == -1){
		return 1;
	}
	return 0;
}

int top(Stack* s){
	return s -> key[s -> top];
}
