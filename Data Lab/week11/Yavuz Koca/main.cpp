#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

#define MAZESIZE 10

typedef struct cell
{
    bool left, right, up, down; // right = false when a wall does not
    char val; // initially this is empty (' '), when the cell is
    bool visited; // this variable will be used while generating maze 
}cell;
cell m[MAZESIZE][MAZESIZE];


void initializeMaze();
void printMaze();
void generateMaze(int, int);
int cellHasUnvisitedNeighbour(int, int);
void removeWall(int, int, int);
bool find_path(cell lab[MAZESIZE][MAZESIZE], int y, int x, int camefrom);

int currentCell_x = 3,currentCell_y = 0;
int totalVisit = 0;
int entrance_x, entrance_y;
int exit_x, exit_y;
stack<pair<int,int> > cellStack;

int main(){
    srand(time(NULL));
    initializeMaze();
    generateMaze(currentCell_x, currentCell_y);
    printMaze();

    cout << "Enter the entrance coordinates" << endl;
    cin >> entrance_x >> entrance_y;
    cout << "Enter the exit coordinates" << endl;
    cin >> exit_x >> exit_y;

    if ( find_path(m, entrance_x, entrance_y, 4) )
        cout << "PATH found" << endl;

    char zz;
    cin >> zz;
    return 0;
}

void initializeMaze(){
    for(int i=0; i<MAZESIZE; i++)
        for(int j=0; j<MAZESIZE; j++){
            m[i][j].left = true;
            m[i][j].right = true;
            m[i][j].up = true;
            m[i][j].down = true;
            m[i][j].val = ' ';
            m[i][j].visited = false;
            if(i == currentCell_x && j == currentCell_y)
                m[i][j].visited = true;
        }
}

void printMaze(){
    for(int i = 0; i < MAZESIZE; i++) {
        for(int j = 0; j < MAZESIZE; j++)
            if(m[i][j].up)
                cout << " -";
            else cout << "  ";

        cout << endl;
        cout << "|";
        for(int j = 0; j < MAZESIZE; j++)
            if(m[i][j].right)
                cout << m[i][j].val << "|";
            else
                cout << m[i][j].val << " ";

        cout << endl;
    }
    for(int i = 0; i < MAZESIZE; i++)
        if(m[MAZESIZE-1][i].down)
            cout << " -";

    cout << endl;
}

void generateMaze(int current_x, int current_y){

    int totalVisit= 0;
    for(int i=0; i<MAZESIZE; i++)
        for(int j=0; j<MAZESIZE; j++)
            if(m[i][j].visited)
                totalVisit++;

    currentCell_x = current_x;
    currentCell_y = current_y;
    m[currentCell_x][currentCell_y].visited = true;

    if(totalVisit == MAZESIZE*MAZESIZE) return;

    int cellHasUnvisitedAdjacent = cellHasUnvisitedNeighbour(currentCell_x, currentCell_y);
    if(cellHasUnvisitedAdjacent){
        pair<int, int> a;
        a.first = currentCell_x;
        a.second = currentCell_y;
        cellStack.push(a);
        removeWall(currentCell_x, currentCell_y, cellHasUnvisitedAdjacent);
        if(cellHasUnvisitedAdjacent == 1)
            currentCell_x--;
        else if(cellHasUnvisitedAdjacent == 2)
            currentCell_y++;
        else if(cellHasUnvisitedAdjacent == 3)
            currentCell_x++;
        else if(cellHasUnvisitedAdjacent == 4)
            currentCell_y--;
    }else if(!cellStack.empty()){
        currentCell_x = cellStack.top().first;
        currentCell_y = cellStack.top().second;
        cellStack.pop();
    }else
        for(int i=0; i<MAZESIZE; i++)
            for(int j=0; j<MAZESIZE; j++)
                if(!m[i][j].visited){
                    currentCell_x = i;
                    currentCell_y = j;
                }

    return generateMaze(currentCell_x, currentCell_y);
}

int cellHasUnvisitedNeighbour(int x, int y){
    vector<int> direction;

    if(y > 0 && !m[x][y-1].visited)
        direction.push_back(4); // LEFT = 4

    if(y < MAZESIZE-1 && !m[x][y+1].visited)
        direction.push_back(2); // RIGHT = 2

    if(x < MAZESIZE-1 && !m[x+1][y].visited)
        direction.push_back(3); // DOWN = 3

    if(x > 0 && !m[x-1][y].visited)
        direction.push_back(1); // UP = 1

    if(direction.size() < 1)
        return 0;

    return direction[rand() % direction.size()];
}

void removeWall(int x, int y, int direction){
    if(direction == 1){
        m[x][y].up = false;
        m[x-1][y].down = false;
    }else if(direction == 2){
        m[x][y].right = false;
        m[x+1][y].left = false;
    }else if(direction == 3){
        m[x][y].down = false;
        m[x+1][y].up = false;
    }else if(direction == 4){
        m[x][y].left = false;
        m[x][y-1].right = false;
    }
}

bool find_path(cell m[MAZESIZE][MAZESIZE], int x, int y, int camefrom){
    m[x][y].val = 'o';
    if ( x == exit_x && y == exit_y) return true;
    printMaze();
    char a;
    cin >> a;
    if ( y > 0 && !m[x][y-1].right && camefrom != 4 )
        if ( find_path(m, x, y-1, 2) ) // go left
            return true;
    if ( x < MAZESIZE - 1 && !m[x+1][y].up && camefrom != 3 )
        if ( find_path(m, x+1, y, 1) ) // go down
            return true;
    if ( x > 0 && !m[x-1][y].down && camefrom != 1 )
        if ( find_path(m, x-1, y, 3)) // go up
            return true;
    if ( y < MAZESIZE - 1 && !m[x][y].right && camefrom != 2)
        if ( find_path(m, x, y+1, 4) ) // go right
            return true;
    m[x][y].val = ' '; // delete incorrect paths
    printMaze(); // display the return from the incorrect paths as well
    return false;
}