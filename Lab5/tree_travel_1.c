#include <stdio.h>
#include <stdlib.h>

struct CompleteTree{
	int Size;
	int nodeNum;
	int* Element;
};

typedef struct CompleteTree* Tree;

Tree CreateTree(int treeSize);
void Insert(Tree t, int value);
void printTree(Tree t);
void printPreorder(Tree t, int index);
void freeTree(Tree t);

void main(int argc, char* argv[]){
	
	FILE *fi; Tree t;
	int treeSize;
	int tmpNum;

	fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &treeSize);
	t = CreateTree(treeSize);
	while(fscanf(fi, "%d", &tmpNum) == 1){
		Insert(t, tmpNum);
	}
	printTree(t);
	freeTree(t);
}

Tree CreateTree(int treeSize){
	Tree t = (Tree)malloc(sizeof(struct CompleteTree));
	t -> Size = treeSize;
	t -> Element = (int*)malloc(sizeof(int) * (treeSize + 1));
	t -> nodeNum = 0;
	return t;
}
void Insert(Tree t, int value){
	if (t -> nodeNum == t -> Size){
		printf("Error! Tree is Full!\n");
		return;
	}	
	t -> Element[++(t -> nodeNum)] = value;
}

void printTree(Tree t){
	printf("Preorder : ");
	printPreorder(t, 1);
	printf("\n");
}

void freeTree(Tree t){
	free(t -> Element);
	free(t);
}

void printPreorder(Tree t, int index){
	if (index <= t -> nodeNum){
		printf("%d ", t -> Element[index]);
		printPreorder(t, 2 * index);
		printPreorder(t, 2 * index + 1);
	}
}
