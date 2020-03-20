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
				tmp = Find(key2, header) ; 
				insert(key1, header, tmp); 
				/* insert(key1, header, header); */
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


List MakeEmpty(){
	Position p = (List)malloc(sizeof(struct Node));
	p -> next = NULL;
	p -> element = -1;
	return p;
}

Position Find(ElementType X, List L){
	if (X == -1){
		return L;
	}
	Position p = L -> next;
	while(p != NULL && p -> element != X){
		p = p -> next;
	}
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
	if (P == NULL){
		printf("Insertion(%d) Failed : cannot find the location to be inserted\n", X);
		return;
	}
	else{
		List tmp = (List)malloc(sizeof(struct Node));
		tmp -> element = X;		
		tmp -> next = P -> next;
		P -> next = tmp;
	}
}

void PrintList(List L){
	for (Position p = L -> next; p != NULL; p = p -> next){
		printf("key:%d\t", p -> element);
	}
	printf("\n");
}

void Delete(ElementType X, List L){
	Position p = FindPrevious(X, L);
	Position trash;
	if (p -> next == NULL){
		printf("Deletion failed : element %d is not in the list\n", X);
		return;
	}
	else{
		trash = p -> next;
		p -> next = trash -> next;	
	}
	free(trash);
	return;
}

Position FindPrevious(ElementType X, List L){
	Position p = L;
	while (p -> next != NULL && p -> next -> element != X){
		p = p -> next;
	}
	return p;
}

void DeleteList(List L){
	Position p = L -> next;
	while (p != NULL){
		free(L);
		L = p;
		p = p -> next;
	}
	free(L);
}
