#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue{
	int* key;
	int head;
	int tail;
	int qsize;
	int max_queue_size;
};

struct _Graph{
	int size;
	int* node;
	int** matrix;
};

//LAB
Graph CreateGraph(int* nodes, int length);
void InsertEdge(Graph g, int a, int b);
void DeleteGraph(Graph g);
void Printing(Graph g);

//HW
void Topsort(Graph g);
Queue MakeNewQueue(int x);
bool IsEmpty(Queue q);
bool IsFull(Queue q);
int Dequeue(Queue q);
void Enqueue(Queue q, int x);
void DeleteQueue(Queue q);
bool didntDo(int* arr, int* index, int j);

int main(int argc, char** argv){
	

	FILE* fp = fopen(argv[1], "r");

	char str[500];
	int arr[500];
	int length = 0, a, b;
	
	fgets(str, 500, fp);
	char* ptr = strtok(str, " ");

	while (ptr != NULL){
		arr[length++] = atoi(ptr);
		ptr = strtok(NULL, " ");
	}

  for (int i = 0; i < length; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
	Graph g = CreateGraph(arr, length);

	fgets(str, 500, fp);
	ptr = strtok(str, " -");
	while(ptr != NULL){
		a = atoi(ptr);	
		ptr = strtok(NULL, " -");
		b = atoi(ptr);
		ptr = strtok(NULL, " -");
		InsertEdge(g, a, b);
	}	

	/* Printing(g); */
	Topsort(g);

	DeleteGraph(g);
}

void Printing(Graph g){
	for (int i = 0; i < g->size; i++){
		if (i == 0){
			printf("   ");
			for (int k = 0; k < g->size; k++){
				printf(" %3d", g->node[k]);
			}
			printf("\n");
		}
		for (int j = 0; j < g->size; j++){
			if (j == 0){
				printf("%3d", g->node[i]);
			}
			printf(" %3d", g->matrix[i][j]);
		}
		printf("\n");
	} 
}

Graph CreateGraph(int* nodes, int length){
	Graph g = (Graph)malloc(sizeof(struct _Graph));
	g->size = length;
	g->node = nodes;
	g->matrix = (int**)malloc(sizeof(int*) * g->size);
	for (int i = 0; i < g->size; i++){
		g->matrix[i] = (int*)malloc(sizeof(int) * g->size);
	}
	return g;
}

void InsertEdge(Graph g, int a, int b){
	for (int i = 0; i < g->size; i++){
		if (g->node[i] == a){
			for (int j = 0; j < g->size; j++){
				if (g->node[j] == b){
					g->matrix[i][j] = 1;
					return;
				}
			}	
		}
	}
}

void DeleteGraph(Graph g){
	for (int i = 0; i < g->size; i++){
		free(g->matrix[i]);
	}	 
	free(g->matrix);
	free(g);
}

void Topsort(Graph g){
	int* arr = (int*)malloc(sizeof(int) * g->size);
	int index = 0;
	Queue q = MakeNewQueue(g->size); 
	while(true){
		for (int j = 0; j < g->size; j++){
			bool allZero = true;
			for (int i = 0; i < g->size; i++){
				if (g->matrix[i][j] != 0){
					allZero = false;
					break;
				}	
			}
			if (allZero && didntDo(arr, &index, j)){
				Enqueue(q, g->node[j]);	
			}
		}
		for (int i = 0; i < index; i++){
			for (int j = 0; j < g->size; j++){
				g->matrix[arr[i]][j] = 0;
			}	
		}
		if (index == g->size){
			break;
		}
	}	
	while(!IsEmpty(q)){
		printf("%d ", Dequeue(q));
	}
	printf("\n");
	DeleteQueue(q);
}

Queue MakeNewQueue(int x){
	Queue q =	(Queue)malloc(sizeof(struct _Queue));
	q->key = (int*)malloc(sizeof(int) * x);
	q->head = 0;
	q->tail = -1;
	q->qsize = 0;
	q->max_queue_size = x;
}

bool IsEmpty(Queue q){
	return q->qsize == 0;
}

bool IsFull(Queue q){
	return q->qsize == q->max_queue_size;
}

int Dequeue(Queue q){
	if (IsEmpty(q)){
		return -1;
	}
	int ans = q->key[q->head++];
	q->head %= q->max_queue_size;
	q->qsize--;
	return ans;
}

void Enqueue(Queue q, int x){
	if (IsFull(q)){
		return;
	}
	q->tail = (q->tail + 1) % q->max_queue_size; 
	q->key[q->tail] = x;
	q->qsize++;
}

void DeleteQueue(Queue q){
	free(q->key);
	free(q);	
}

bool didntDo(int* arr, int* index, int j){
	bool check = true;
	for (int i = 0; i < *index; i++){
		if (arr[i] == j){
			check = false;
		}
	}
	if (check){
		arr[(*index)++] = j;
	}
	return check;
}
