#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

Tree insertNode(Tree root, int key);
Tree deleteNode(Tree root, int key, bool re);
void findNode(Tree root, int key);
void printInorder(Tree root);
void deleteTree(Tree root);
Tree getMaxValueInTree(Tree parentNode, Tree node);


void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree root = NULL;

	while(!feof(fi)){
		fscanf(fi, "%c", &cv);
		switch(cv){
			case 'i':
				fscanf(fi, "%d", &key);
				root = insertNode(root, key);
				break;
			case 'd':
				fscanf(fi, "%d", &key);
				deleteNode(root, key, false);
				break;
			case 'f':
				fscanf(fi, "%d", &key);
				findNode(root, key);
				break;
			case 'p':
				fscanf(fi, "%c", &cv);
				if(cv == 'i'){
					printInorder(root);
				}
				printf("\n");
				break;
		}
	}
	deleteTree(root);
}

Tree insertNode(Tree root, int key){
	if (root == NULL){
		root = (Tree)malloc(sizeof(struct BinarySearchTree));
		root -> value = key;
		root -> right = NULL;
		root -> left = NULL;    
		printf("insert %d\n", key);
	}
	else if (root -> value == key){
		printf("Insertion Error : There is already %d in the tree.\n", key);
	}
	else if (root -> value < key){
		root -> right = insertNode(root -> right, key);
	}
	else{
		root -> left = insertNode(root -> left, key);
	}
	return root;
}

Tree deleteNode(Tree root, int key, bool re){
	if (root == NULL){
		printf("Deletion Error : %d is not in the tree\n", key);
	}
	else if(root -> value < key){
		root -> right = deleteNode(root -> right, key, re);
	}
	else if(root -> value > key){
		root -> left = deleteNode(root -> left, key, re);
	}
	else{
		Tree tmp;
		if (root -> right && root -> left){
			tmp = getMaxValueInTree(root, root -> left); 			
			if (tmp == NULL){
				printf("error in deleteNode.\n");
				return NULL;
			}
			root -> value = tmp -> value;
			if (re == false){
				printf("Delete %d\n", key);
				re = true;
			}
			root -> left = deleteNode(root -> left, tmp -> value, re);
		}
		else{
			tmp = root;
			if (tmp -> right == NULL){
				root = root -> left;
			}
			else{
				root = root -> right;
			}
			free(tmp);
			if (re == false){
				printf("Delete %d\n", key);
				re = true;
			}
		}
	}
	return root;
}

void findNode(Tree root, int key){
	if (root == NULL){
		printf("%d is not in the tree\n", key);
	}
	else if (root -> value == key){
		printf("%d is in the tree\n", key);
	}
	else if (root -> value < key){
		findNode(root -> right, key);
	}
	else {
		findNode(root -> left, key);
	}
}

void printInorder(Tree root){
	if (root == NULL){
		return;
	}
	printInorder(root -> left);
	printf("%d ", root -> value);
	printInorder(root -> right);
}

void deleteTree(Tree root){
	if (root == NULL){
		return;
	}
	deleteTree(root -> left);
	deleteTree(root -> right);
	free(root);
}

Tree getMaxValueInTree(Tree parentNode, Tree node){
	if (node == NULL){
		printf("Parent is NULL");	
		return NULL;
	}

	else if (node -> right == NULL){
		return node;	
	}
	else{
		getMaxValueInTree(node, node -> right);
	}
}
