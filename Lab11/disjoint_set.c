#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
  int sizeMaze;
  int* cells;
  int* walls;
} DisjointSets;

void init(DisjointSets* sets, int num);
void Union(DisjointSets* sets, int i, int j);
int find(DisjointSets* sets, int i);
void createMaze(DisjointSets* sets, int num);
void printMaze(DisjointSets* sets, int num);
void freeMaze(DisjointSets* sets);

int main(int argc, char* argv[]) {
  int num, i;
  FILE* fp = fopen(argv[1], "r");
  DisjointSets* sets;
  fscanf(fp, "%d", &num);
  sets = (DisjointSets*)malloc(sizeof(DisjointSets));
  init(sets, num);
  srand(time(NULL));
  createMaze(sets, num);
  printMaze(sets, num);
  freeMaze(sets);
  fclose(fp);

  return 0;
}

void init(DisjointSets* sets, int num){
  sets->sizeMaze = num * num;
  sets->cells = (int*)malloc(sizeof(int) * (sets->sizeMaze + 1));
  sets->walls = (int*)malloc(sizeof(int) * (2 * sets->sizeMaze + 1));
  for (int i = 1; i <= sets->sizeMaze; i++){
    sets->cells[i] = 0;
  }
  for (int i = 1; i < 2 * sets->sizeMaze; i++){
    sets->walls[i] = 1; 
  }
  sets->walls[2 * sets->sizeMaze] = 0;
}
void Union(DisjointSets* sets, int i, int j){
  if (sets->cells[i] < sets->cells[j]) {
    sets->cells[j] = i;
  }
  else if (sets->cells[i] > sets->cells[j]){
    sets->cells[i] = j; 
  }
  else {
    sets->cells[i]--;
    sets->cells[j] = i;
  }
}

int find(DisjointSets* sets, int i) {
  if (sets->cells[i] <= 0){
    return i;
  }
  else {
    return find(sets, sets->cells[i]);
  }
}

void createMaze(DisjointSets* sets, int num){

  int unionNumber = 0;

  while (unionNumber != sets->sizeMaze - 1){
    int pos = rand() % (sets->sizeMaze) + 1;
    int target;
    int direction;  
    if (pos == sets->sizeMaze){
      continue;
    }
    else if (pos % num == 0){
      direction = 1;
      target = pos + num;
    }
    else if (pos > num * (num - 1)){
      direction = 0;
      target = pos + 1;
    }
    else {
      direction = rand() % 2;
      target = pos + (direction == 1 ? num : 1);
    }

    if (find(sets, pos) != find(sets, target)){
      Union(sets, find(sets, pos), find(sets, target));
      unionNumber++;
      sets->walls[2 * pos - direction] = 0;
    }
  }
}
void printMaze(DisjointSets* sets, int num) {
  printf(" ");
  for (int i = 0; i < num; i++){
    printf("_ ");
  }
  printf("\n");
  for (int i = 1; i <= sets->sizeMaze; i++){
    if (i == 1){
      printf(" ");
    }
    else if (i % num == 1){
      printf("|");
    }
    printf("%s", sets->walls[2 * i - 1] == 1 ? "_" : " ");  
    printf("%c", sets->walls[2 * i] == 1 ? '|' : ' ');  
    if (i % num == 0 && i != sets->sizeMaze){
      printf("\n");
    }
  }
  printf("\n");
}
void freeMaze(DisjointSets* sets){
  free(sets->cells);
  free(sets->walls);
  free(sets);
}
