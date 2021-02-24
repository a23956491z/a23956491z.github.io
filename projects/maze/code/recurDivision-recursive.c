#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 25
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define WALL 1
#define ROAD 0
#define GOAL 2
#define TRACE 3

#define MAX_OF_GRID SIZE*SIZE

//#define EXPERIMENT_MODE

typedef struct Grid
{
	struct Grid *dir[4];
	int state;
}Grid;

typedef struct
{
	Grid* data[SIZE * SIZE];
	int top;
	int lock;
}List;



int isEmpty(List *l){
    return l->top == -1;
}

List* initList(){

    List *tmp = (List*)malloc(sizeof(List));

    tmp->top = -1;
    tmp->lock = 0;
    for(int i = 0; i != MAX_OF_GRID; i++) tmp->data[i] = NULL;

    return tmp;
}

Grid* initGrid(int state){

    Grid *tmp = (Grid*)malloc(sizeof(Grid));

    tmp->state = state;

    return tmp;
}
/*
Insert an element from top
*/
void addElement(List *l, Grid *g)
{
    if(l->lock) return;
    if(l->top == MAX_OF_GRID-1){
        printf("%s\n", "stack is full can't add element!");
        return;
    }

    (l->data)[++(l->top)] = g;
}

/*
remove an element from top and return a pointer point to the element.
If list is empty, return NULL.
*/
Grid *removeElement(List *l)
{
    if(l->lock) return NULL;
    if(isEmpty(l)) return NULL;

    Grid *tmp = l->data[l->top];
    l->top--;

    return tmp;
}

typedef struct
{
	int row, col;
}Node;
/*
	Use for store passages on walls we made,
	checking the new wall won't block these passages.
*/
typedef struct{
	int passage[SIZE][SIZE];
}Passage;
void recur_division_verti(int **m, Node n1, Node n2,Passage *pas);
void recur_division_hori(int **m, Node n1, Node n2, Passage *pas){

	int row_diff = n2.row - n1.row;
	int col_diff = n2.col - n1.col;
	if(row_diff <= 2) return;
	if(col_diff <= 2) return;
	/*
		If column sapce is much more than row space,
		then do the vertical division instead of horizantal one.
	*/
	if(col_diff - row_diff > 2) {
		recur_division_verti(m, n1, n2, pas);
		return;
	}

	//printMaze(m);

	int half_y = (n2.row + n1.row) / 2;

	for(int i = n1.col; i != n2.col; i++){
		/*
			Check if there any passage we made on walls,
			beside the wall we gonna add,
			preventing the new wall to block the passage.
		*/
		if(i == n2.col-1 && i != SIZE-1){
			if(pas->passage[half_y][i+1]) continue;
		}
		else if(i == n1.col && i != 0){
			if(pas->passage[half_y][i-1]) continue;
		}
		m[half_y][i] = 1;
	}
	/*
		"Erase passge", create a little tunnel on wall.
	*/
	int random_x = ( rand() % (col_diff)) + n1.col;
	pas->passage[half_y][random_x] = 1;
	m[half_y][random_x] = 0;

	/*
		Ramdonly choose vertical division or horizantal division
		and recursive both on upper side & lower side.
	*/
	Node n3 = {.row = half_y, .col = n2.col};
	if(rand() %2) recur_division_verti(m, n1,n3, pas);
	else recur_division_hori(m,n1,n3, pas);

	Node n4 = {.row = half_y+1, .col = n1.col};
	if(rand() %2) recur_division_verti(m, n4, n2, pas);
	else recur_division_hori(m, n4, n2, pas);
}

void recur_division_verti(int **m, Node n1, Node n2, Passage *pas){

	int row_diff = n2.row - n1.row;
	int col_diff = n2.col - n1.col;
	if(row_diff <= 2) return;
	if(col_diff <= 2) return;
	/*
		If row sapce is much more than column space,
		then do the horizantal division instead of vertical one.
	*/
	if(row_diff - col_diff > 2) {
		recur_division_hori(m, n1, n2, pas);
		return;
	}
	//printMaze(m);


	int half_x = (n2.col + n1.col) / 2;
	for(int i = n1.row; i != n2.row; i++){
		/*
			Check if there any passage we made on walls,
			beside the wall we gonna add,
			preventing the new wall to block the passage.
		*/
		if(i == n2.row-1 && i != SIZE-1){
			if(pas->passage[i+1][half_x]) continue;
		}else if(i == n1.row && i != 0){
			if(pas->passage[i-1][half_x]) continue;
		}
		m[i][half_x] = 1;
	}
	/*
		"Erase passge", create a little tunnel on wall.
	*/
	int random_y = (rand()% row_diff) + n1.row;
	pas->passage[random_y][half_x] = 1;
	m[random_y][half_x] = 0;
	/*
		Ramdonly choose vertical division or horizantal division
		and recursive both on left side & right side.
	*/
	Node n3 = {.row = n2.row, .col = half_x};
	if(rand()%2) recur_division_hori(m, n1, n3, pas);
	else recur_division_verti(m, n1, n3, pas);

	Node n4 = {.row = n1.row, .col = half_x+1};
	if(rand()%2) recur_division_hori(m, n4, n2, pas);
	else recur_division_verti(m, n4, n2, pas);
}


void printMaze_node(int **m)
{
	int j, k;
	for(j = 0;j < SIZE;j ++)
	{
		for(k = 0;k < SIZE;k ++)
		{
			if(m[j][k] == 0)
				printf(" ");
			else if(m[j][k] == 1)
				printf("O");
		}
		printf("\n");
	}
	printf("----------\n");
}
void generate_maze_to_array(int ***m){

	*m = (int**)calloc(SIZE, sizeof(int*));
	int *array_start = (int*)calloc(SIZE*SIZE, sizeof(int));
	for(int i = 0; i != SIZE; i++) (*m)[i] = array_start+ i*SIZE;

	Node n1 = {.row = 0, .col = 0};
	Node n2 = {.row = SIZE, .col = SIZE};
	Passage *pas = (Passage*)malloc(sizeof(Passage));
	if(rand()%2) recur_division_hori(*m, n1, n2, pas);
	else recur_division_verti(*m, n1, n2, pas);

	free(pas);
}
/*
function initMaze
Alocate a 2-D link list with s * s sizes as the map of maze.
Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
The gird in left top is start point and right bottom is finish point.
Randomly generate 20% wall in the maze.
Make sure start point and finish point are 0
*/

void initMaze(Grid **m, int s)
{

/*
    int default_grid[SIZE][SIZE] ={{0,0,0,0,1,1,0,1,1,1},
                                   {1,1,1,0,1,1,0,0,0,0},
                                   {1,1,0,0,0,0,0,1,1,0},
                                   {1,1,0,1,1,1,1,1,1,1},
                                   {0,0,0,0,0,0,0,0,0,0},
                                   {0,1,0,1,1,0,1,0,1,0},
                                   {0,1,0,0,1,0,1,0,1,1},
                                   {0,1,1,1,1,1,1,1,1,0},
                                   {0,0,0,0,0,0,0,0,0,0},
                                   {1,1,1,1,1,1,1,1,1,2}};
*/
	int **random_gen ;
	generate_maze_to_array(&random_gen);

    Grid * UPPER[SIZE];
    for(int j = 0; j != SIZE; j++) UPPER[j] = NULL;

//    int wall = 0;

    for(int i = 0; i != SIZE; i++){

        Grid * left_one = NULL;

        for(int j = 0; j != SIZE; j++){

            Grid *tmp = NULL;

            if(i ==SIZE-1 && j == SIZE-1) tmp = initGrid(GOAL);
            else if(i == 0 && j == 0)   tmp = initGrid(ROAD);
            else{
				tmp = initGrid(random_gen[i][j]);
/*
                int build_wall = rand() % 4 == 0;
                tmp = initGrid((build_wall && wall < SIZE*SIZE*0.2));
                if(build_wall)wall++;
*/
            }

            tmp->dir[UP] = UPPER[j];
            tmp->dir[LEFT] = left_one;
            tmp->dir[RIGHT] = NULL;
            tmp->dir[DOWN] = NULL;

            if(left_one != NULL) left_one->dir[RIGHT] = tmp;
            if(UPPER[j] != NULL) UPPER[j]->dir[DOWN] = tmp;

            if(i == 0 && j == 0) *m = tmp;

            UPPER[j] = tmp;
            left_one = tmp;
        }
        //printf("\n");
    }

	free(random_gen[0]);
	free(random_gen);


}

/*
function findPath
This function will find a path between start point and finish point.
Return a list content the path information inside.
If there is no path between two point then the list will be empty.

*/
void printMaze(Grid *m);
void recursive_path(List * lst, Grid *head, Grid *g){

    if(g == NULL) return;
    if(g->state == WALL || g->state == TRACE) return;
    if(lst->lock) return;

	addElement(lst, g);
    if(g->state == GOAL) {
        addElement(lst, g);
        lst->lock = 1;

		#ifndef EXPERIMENT_MODE
	        printMaze(head);
		#endif
		return;

	}
    g->state = TRACE;

    recursive_path(lst, head, g->dir[RIGHT]);
    recursive_path(lst, head, g->dir[DOWN]);
    recursive_path(lst, head, g->dir[LEFT]);
    recursive_path(lst, head, g->dir[UP]);

    Grid * tmp =removeElement(lst);
	free(tmp);
}

List *findPath(Grid *m)
{
    List* l = initList();
    recursive_path(l, m, m);
    return l;

}

void printPath(List *l)
{
	int j;
	for(j = 1;j < l->top;j ++)
	{
		if(l->data[j] == l->data[j - 1]->dir[UP])
		{
			printf("UP");
		}
		else if(l->data[j] == l->data[j - 1]->dir[DOWN])
		{
			printf("DOWN");
		}
		else if(l->data[j] == l->data[j - 1]->dir[LEFT])
		{
			printf("LEFT");
		}
		else if(l->data[j] == l->data[j - 1]->dir[RIGHT])
		{
			printf("RIGHT");
		}
		printf(" ");
	}
	printf("\n");
}

void printMaze(Grid *m)
{
	Grid *j = m, *k;
	for(int i = 0; i != SIZE+2; i++){
		printf("O ");
	}printf("\n");
	while(j != NULL)
	{
		k = j;
		printf("O ");
		while(k != NULL)
		{
			switch (k->state) {
				case TRACE:
					printf(". ");
					break;

				case ROAD:
					printf("  ");
					break;
				case WALL:
					printf("O ");
					break;
				default:
					printf(". ", k->state);
			}

			k = k->dir[RIGHT];
		}
		printf("O\n");
		j = j->dir[DOWN];
	}

	for(int i = 0; i != SIZE+2; i++){
		printf("O ");
	}printf("\n");



}

void test_list(){
    List *lst = initList();

    const int TEST_ARR_SIZE = 3;
    Grid * arr[TEST_ARR_SIZE];
    for(int i = 0; i != TEST_ARR_SIZE; i++){
        arr[i] = (Grid*)malloc(sizeof(Grid));
        arr[i]->state = i;

        addElement(lst, arr[i]);
    }

    int lst_size = lst->top + 1;
    for(int i = 0; i != lst_size; i++){
        Grid *pop_out = removeElement(lst);
        if(pop_out != NULL){
            printf("%d\n", pop_out->state);
        }else{
            printf("%s\n", "stack is empty cant pop!");
        }
		free(pop_out);

    }
    for(int i = 0; i != TEST_ARR_SIZE; i++)    free(arr[i]);
    free(lst);


}

int main()
{
		srand(time(NULL));
    //test_list();
	const int TEST_SAMPLE = 1;
	int failed = 0;

	for(int i = 0; i != TEST_SAMPLE; i++)
	{
		Grid *maze = NULL;
		initMaze(&maze, SIZE);



	    List *path = findPath(maze);
	    if(path->lock == 0){
			#ifndef EXPERIMENT_MODE
				printMaze(maze);
		        printf("Can't EXIT\n");
			#endif
			failed++;
	    }

		#ifndef EXPERIMENT_MODE
		//printPath(path);
			for(int i = 0; i != SIZE*2; i++) printf("-");
			printf("\n");
		#endif

		free(path);
	}
	#ifdef EXPERIMENT_MODE
	printf("samples : %d failed : %d\n", TEST_SAMPLE, failed);
	#endif

	return 0;
}
