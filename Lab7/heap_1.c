#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct{
	int capacity;
	int size;
	int* element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap* heap, int value);
int Find(Heap* heap, int value);
int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);
void swap(int* x, int* y);

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while(!feof(fi)){
		fscanf(fi, "%c", &cv);
		switch(cv){
			case 'n' : fscanf(fi, "%d", &heapSize);
				maxHeap = CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fi, "%d", &key);
				Insert(maxHeap, key);
				break;
			case 'd':
				DeleteMax(maxHeap);
				break;
			case 'p':
				PrintHeap(maxHeap);
				break;
			case 'f':
				fscanf(fi, "%d", &key);
				if (Find(maxHeap, key))
					printf("%d is in the tree,\n", key);
				else
					printf("%d is not in the tree.\n", key);
				break;
		}
	}
}


Heap* CreateHeap(int heapSize){
	Heap* tmp = (Heap*)malloc(sizeof(Heap));
	tmp -> element = (int*)malloc(sizeof(int) * (heapSize + 1));
	tmp -> size = 0;
	tmp -> capacity = heapSize;
	return tmp;
}

void Insert(Heap* heap, int value){
	if (heap -> size == heap -> capacity){
		printf("Insertion Error : Max Heap is full.\n");
		return;
	}
	else{
		if (Find(heap, value)){
			printf("%d is already in the heap.\n", value);
			return;
		}	
		heap -> element[++(heap -> size)] = value;
		printf("insert %d\n", value);
		for (int i = heap -> size; i / 2 > 0; i /= 2){
			if (heap -> element[i] > heap -> element[i / 2]){
				swap(&(heap -> element[i]), &(heap -> element[i / 2]));
			}
			else{
				break;
			}
		}
	}
}

int Find(Heap* heap, int value){
	for (int i = 1; i <= heap -> size; i++){
		if (heap -> element[i] == value){
			return 1;
		}
	}
	return 0;
}

int DeleteMax(Heap* heap){
	if (heap -> size == 0){
		printf("Deletion Error : Max heap is empty!\n");
		return -1;
	}
	else{
		int index = 1;
		int ans = heap -> element[1];
		while(1){
			if (2 * index + 1 > heap -> size){
				heap -> element[index] = heap -> element[heap -> size];
				break;
			}
			else {
				int higher = (heap -> element[2 * index] > heap -> element[2 * index + 1]) ? 2 * index : 2 * index + 1;
				if (heap -> element[higher] < heap -> element[heap -> size]){
					heap -> element[index] = heap -> element[heap -> size];
					break;
				}
				else{
					heap -> element[index] = heap -> element[higher];
					swap(&(heap -> element[index]), &(heap -> element[higher]));
					index = higher;
				}
			}
		}
		heap -> size--;
		printf("Max Element : %d deleted\n", ans);
		return ans;
	}
}

void PrintHeap(Heap* heap){
	if (heap -> size == 0){
		printf("Print Error : Max heap is empty!\n");
	}
	else{
		for (int i = 1; i <= heap -> size; i++){
			printf("%d ", heap -> element[i]);
		}
		printf("\n");
	}
}

void swap(int* x, int* y){
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
