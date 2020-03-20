#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

typedef struct AVLNode* AVLTree;
typedef AVLTree Position;
typedef int ElementType;
typedef struct AVLNode{
	ElementType element;
	AVLTree left;
	AVLTree right;
	int height;
}AVLNode;

AVLTree insert(ElementType x, AVLTree t);
void printInorder(AVLTree t);
void deleteTree(AVLTree t);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
bool needRotate(AVLTree t);
void changeHeight(AVLTree t);
int max(int x, int y);

int main(int argc, char **argv){
	
	FILE* fp = fopen(argv[1], "r");
	AVLTree myTree = NULL;
	int num;

	if (fp == NULL){
		printf("There is no file : %s\n", argv[1]);
		exit(-1);
	}

	while (fscanf(fp, "%d", &num) != EOF){
		
		myTree = insert(num, myTree);
		printInorder(myTree);
		printf("\n");
	}

	deleteTree(myTree);
	return 0;
}

AVLTree insert(ElementType x, AVLTree t){
	if (t == NULL){
		t = (AVLTree)malloc(sizeof(AVLNode));
		if (t == NULL){
			printf("Out of space!!!\n");
			return NULL;
		}
		t->left = NULL;
		t->right = NULL;
		t->element = x;
		t->height = 0;
	}	
	else {
		if (x < t->element){
			t->left = insert(x, t->left);	
			changeHeight(t);
			if (needRotate(t)){
				if (x < t->left->element){
					t = SingleRotateWithLeft(t);
				}
				else{
					t = DoubleRotateWithLeft(t);	
				}
			}
		}	
		else if (x > t->element){
			t->right = insert(x, t->right);
			changeHeight(t);
			if (needRotate(t)){
				if (x > t->right->element){
					t = SingleRotateWithRight(t);	
				}
				else{
					t = DoubleRotateWithRight(t);
				}
			}
		}
		else {  // x == t->element
			printf("[Error] %d already in the tree!\n", x);	
		}
	}
	return t;
}

void printInorder(AVLTree t){
	if (t == NULL){
		return;
	}
	printInorder(t->left);
	printf("%d(%d) ", t->element, t->height);
	printInorder(t->right);
}

void deleteTree(AVLTree t){
	if (t == NULL){
		return;
	}
	deleteTree(t->left);
	deleteTree(t->right);
	free(t);
}

Position SingleRotateWithLeft(Position node){
	Position tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;

	changeHeight(node);
	changeHeight(tmp);

	return tmp;
}

Position SingleRotateWithRight(Position node){
	Position tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;

	changeHeight(node);
	changeHeight(tmp);

	return tmp;
}

Position DoubleRotateWithLeft(Position node){
	node->left = SingleRotateWithRight(node->left);
	return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node){
	node->right = SingleRotateWithLeft(node->right);
	return SingleRotateWithRight(node);
}

bool needRotate(AVLTree t){
		int leftHeight = (t->left == NULL) ? -1 : t->left->height;
		int rightHeight = (t->right == NULL) ? -1 : t->right->height;
		int diff = leftHeight - rightHeight;
		if (diff == 2 || diff == -2) return true;
		else return false;
}

void changeHeight(AVLTree t){
		int leftHeight = (t->left == NULL) ? -1 : t->left->height;
		int rightHeight = (t->right == NULL) ? -1 : t->right->height;
		t->height = max(leftHeight, rightHeight) + 1;
}

int max(int x, int y){
	return (x > y) ? x : y;
}
