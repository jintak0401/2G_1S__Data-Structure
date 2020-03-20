#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
	ElementType element;
	Position next;
};

List MakeEmpty();
int IsEmpty(List L);
int isLast(Position P, List L);
void insert(ElementType X, List L, Position P);
void PrintList(List L);

void Delete(ElementType X, List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void DeleteList(List L); 

int main(int argc, char *argv[]){
	char command;
	int key1, key2;
	FILE *input;
	Position header;
	Position tmp;
	if(argc == 1){
		printf("No input file\n");
		return 0;
	}
	else{
		input = fopen(argv[1], "r");
	}
	header = MakeEmpty();
	while(1){
		command = fgetc(input);
		if(feof(input)) break;
		switch(command){
			case 'i':
				fscanf(input, "%d %d", &key1, &key2);
				//tmp = Find(key2, header) ; hw3
				//insert(key1, header, tmp); hw3
				insert(key1, header, header);
				break;
			case 'd':
				fscanf(input, "%d", &key1);
				Delete(key1, header);
				break;
			case 'f':
				fscanf(input, "%d", &key1);
				tmp = FindPrevious(key1, header);
				if(isLast(tmp, header))
					printf("Could not find %d in the list\n", key1);
				else{
					if (tmp -> element > 0)
						printf("Key of the previous node of %d is %d\n", key1, tmp -> element);
					else
						printf("Key of the previous node of %d is header.\n", key1);
				}
				break;
			case 'p':
				PrintList(header);
				break;
			default:
				break;
		}
	}
	DeleteList(header); // free all memory used by linked list
	fclose(input);
	return 0;
}

/* void Insert(ElementType X, List L, ElementType Y){
 *   if (Y == -1){
 *     Position tmp = (Position)malloc(sizeof(struct Node));			
 *     tmp -> next = head -> next;
 *     head -> next = tmp;
 *   }
 *   else{
 *     Find(ElementType X, List L);	
 *   }
 * } */

List MakeEmpty(){
	Position p = (List)malloc(sizeof(struct Node));
	p -> next = NULL;
	p -> element = -1;
	return p;
}

int IsEmpty(List L){
	if (L -> next == NULL){
		return 1;
	}
	else {
		return 0;
	}
}

int isLast(Position P, List L){
	if (P -> next == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

void insert(ElementType X, List L, Position P){
	Position tmp = (Position)malloc(sizeof(struct Node));
	tmp -> next = P -> next;
	P -> next = tmp;
	tmp -> element = X;
}

void PrintList(List L){
	for (Position p = L -> next; p != NULL; p = p -> next){
		printf("key:%d\t", p -> element);
	}
	printf("\n");
}

void Delete(ElementType X, List L){}
Position Find(ElementType X, List L){}
Position FindPrevious(ElementType X, List L){}
void DeleteList(List L){}
