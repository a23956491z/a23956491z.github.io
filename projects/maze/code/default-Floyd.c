#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10
#define STACK_MAX SIZE*SIZE

#define WALL 1
#define ROAD 0
#define GOAL 2
#define TRACE 3

const int inf = SIZE*SIZE+1;

typedef struct
{
	int row, col;
}Node;

typedef struct
{
	Node *data[SIZE * SIZE];
	int top;
}List;

int pos(int i , int j){
	return i*SIZE+j;
}

List* initList(){

    List *tmp = (List*)malloc(sizeof(List));

    tmp->top = -1;
    for(int i = 0; i != STACK_MAX; i++)
		tmp->data[i] = (Node*)malloc(sizeof(Node));

    return tmp;
}
/*
Insert an element from top
*/
void addElement(List *l, int r, int c)
{
	if(l->top == STACK_MAX)return;
	Node *tmp = l->data[++l->top];
	tmp->row = r;
	tmp->col = c;
}

/*
remove an element from top and return a pointer point to the element.
If list is empty, return NULL.
*/
Node *removeElement(List *l)
{
	if(l->top == -1) return NULL;
	Node *pop_out = l->data[l->top];

	l->top--;
	return pop_out;
}

void printPath(List *l)
{
	if(l == NULL)
		return;
	int j;
	for(j = 0;j < l->top+1;j ++)
	{
		printf("(%d, %d) ", l->data[j]->row, l->data[j]->col);
	}
}

void printMaze(int **m)
{
	int j, k;
	for(j = 0;j < SIZE;j ++)
	{
		for(k = 0;k < SIZE;k ++)
		{
			if(m[j][k] == ROAD)
				printf("  ");
			else if(m[j][k] == WALL)
				printf("O ");
			else if(m[j][k] == TRACE){
				printf(". ");
			}
		}
		printf("\n");
	}
	for(int i = 0; i != SIZE; i++) printf("--");
	printf("\n");
}
/*
function initMaze
Alocate a 2-D array with s * s sizes as the map of maze.
Inside the maze where 0 represent empty space and 1 represent wall.
[0][0] is start point and [s - 1][s - 1] is finish point.
Randomly generate 20% wall in the maze.
Make sure [0][0] and [s - 1][s - 1] are 0
*/
void initMaze(int ***m, int s)
{
	*m = (int**)calloc(s, sizeof(int*));
	int *array_start = (int*)calloc(s*s, sizeof(int));
	for(int i = 0; i != s; i++) (*m)[i] = array_start+ i*s;

	int default_grid[SIZE][SIZE] ={{0,0,0,0,1,1,0,1,1,1},
                                   {1,1,1,0,1,1,0,0,0,0},
                                   {1,1,0,0,0,0,0,1,1,0},
                                   {1,1,0,1,1,1,1,1,1,1},
                                   {0,0,0,0,0,0,0,0,0,0},
                                   {0,1,0,1,1,0,1,0,1,0},
                                   {0,1,0,0,1,0,1,0,1,1},
                                   {0,1,1,1,1,1,1,1,1,0},
                                   {0,0,0,0,0,0,0,0,0,0},
                                   {1,1,1,1,1,1,1,1,1,0}};
	for(int i = 0; i != SIZE; i++){
		for(int j = 0; j != SIZE; j++){
			(*m)[i][j] = default_grid[i][j];
		}
	}

	printMaze(*m);
}

/*
function findPath
This function will find a path between start point and finish point.
Return a queue content the path information inside.
If there is no path between two point then the queue will be empty.
*/
List *findPath(int **m, int s)
{
	int dis_grid[SIZE*SIZE][SIZE*SIZE];

	for(int i = 0; i != SIZE*SIZE; i++){
		for(int j = 0; j != SIZE*SIZE; j++){
			dis_grid[i][j] = inf;
		}
	}
	for(int i = 0; i != SIZE; i++){
		for(int j = 0; j != SIZE; j++){
			if(m[i][j] == 0){
				dis_grid[pos(i,j)][pos(i,j)] = 0;
				if(i != SIZE-1 && m[i+1][j] == 0)
					dis_grid[pos(i+1,j)][pos(i,j)] = dis_grid[pos(i,j)][pos(i+1,j)] = 1;
				if(j != SIZE-1 && m[i][j+1] == 0)
					dis_grid[pos(i,j+1)][pos(i,j)] = dis_grid[pos(i,j)][pos(i,j+1)] = 1;
			}
		}
	}

	for(int k = 0; k != SIZE*SIZE; k++){
		for(int i = 0; i != SIZE*SIZE; i++){
			for(int j = 0; j != SIZE*SIZE; j++){
				if(dis_grid[i][j] > dis_grid[i][k] + dis_grid[k][j])
					dis_grid[i][j] =  dis_grid[i][k] + dis_grid[k][j];
			}
		}
	}

	int goal_pos =pos(SIZE-1,SIZE-1);
	int goal_dis = dis_grid[0][goal_pos];

	int i=0,j =0;
	List* shortest_path = initList();
	while(goal_dis-- != -1){

		addElement(shortest_path, i, j);
		m[i][j] = TRACE;

		if(goal_dis == -1) break;
		if(j != SIZE-1 	&& goal_dis == dis_grid[goal_pos][pos(i,j+1)]) j++;
		if(j != 0 		&& goal_dis == dis_grid[goal_pos][pos(i,j-1)]) j--;
		if(i != SIZE-1 	&& goal_dis == dis_grid[goal_pos][pos(i+1,j)]) i++;
		if(j != 0 		&& goal_dis == dis_grid[goal_pos][pos(i-1,j)]) i--;
	}
	printMaze(m);
	return shortest_path;
}



int main()
{
	int **maze;
	initMaze(&maze, SIZE);
	printPath(findPath(maze, SIZE));

	free(*maze);
	free(maze);
	return 0;
}
