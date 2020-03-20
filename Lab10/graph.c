#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct Node{
	int vertex;
	int dist;
	int finalPrev;
	int tmpPrev;
}Node;

typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;

Graph createGraph(int size);
Node* createNode(int size);
void printShortestPath(Graph g);

void main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1], "r");
	Graph g;

	int size;
	fscanf(fi, "%d\n", &size);
	g = createGraph(size + 1);
	char temp = 0;
	while(temp != '\n'){
		int node1, node2, weight;
		fscanf(fi, "%d-%d-%d", &node1, &node2, &weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
}

Graph createGraph(int size){
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->size = size;
	g->vertices = (int**)malloc(sizeof(int*) * size);
	g->nodes = createNode(size);	
	for (int i = 0; i < size; i++){
		g->vertices[i] = (int*)malloc(sizeof(int) * size);
		for (int j = 0; j < size; j++){
			g->vertices[i][j] = 0;	
		}
	}
	return *g;
}
Node* createNode(int size){
	Node* nodes = (Node*)malloc(sizeof(Node) * size); 
	for (int i = 1; i < size; i++){
		Node* node = (Node*)malloc(sizeof(Node));
		node->vertex = i;
		node->tmpPrev = NULL;
		node->finalPrev = NULL;
		node->dist = INT_MAX;
		nodes[i] = *node;	
	}	
	nodes[1].dist = 0;
	nodes[1].finalPrev = 1;
	return nodes;
}
void printShortestPath(Graph g){
	while(true){
		for (int i = 1; i < g.size; i++){
			if (g.nodes[i].dist != INT_MAX){
				for (int j = 1; j < g.size; j++){
					if (g.vertices[i][j] != 0 && g.vertices[i][j] + g.nodes[i].dist < g.nodes[j].dist){
						g.nodes[j].dist = g.vertices[i][j] + g.nodes[i].dist;	
						g.nodes[j].tmpPrev = i;
					}
				}
			}
		}
		int min = INT_MAX;		
		int index = -1;
		for (int i = 1; i < g.size; i++){
			if (g.nodes[i].finalPrev == NULL && g.nodes[i].dist < min){
				min = g.nodes[i].dist;
				index = i;
			}	
		}	
		if (index < 0){
			break;
		}
		else{
			g.nodes[index].finalPrev = g.nodes[index].tmpPrev;	
		}
	}
	for (int i = 2; i < g.size; i++){
		if (g.nodes[i].finalPrev != NULL){
			int vertex = g.nodes[i].vertex;
			int index = 0;
			int* arr = (int*)malloc(sizeof(int) * g.size);	
			while (vertex != 1){
				arr[index++] = vertex;
				vertex = g.nodes[vertex].finalPrev;
			}	
			arr[index++] = 1;
			for (int i = index - 1; i > 0; i--){
				printf("%d -> ", arr[i]);
			}  
			printf("%d (cost : %d)\n", g.nodes[i].vertex, g.nodes[i].dist);
			free(arr);
		}
		else{
			printf("Cannot reach to node %d\n", i);
		}
	}
}
