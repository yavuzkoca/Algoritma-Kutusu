#include <iostream>
#include <stack>
#include <cstdlib>
#include "Player.h"

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define EXIT_X 13
#define EXIT_Y 21

using namespace std;

typedef struct d{
    int x;
    int y;
    int right;
    int left;
    int down;
    int up;
    int camefrom;
}StackDataType, position;

struct Node{
    StackDataType data;
    Node *next;
};

void printMaze();
void printMaze2();

char Maze[14][22] =
        {
                "#o###################",
                "#     #      #    # #",
                "# ### # ###### ## # #",
                "# # #        # #  # #",
                "# # ### ######## ## #",
                "#     # # ##   #    #",
                "### # # # ## # # ####",
                "# # # # #    #      #",
                "# # # # # ######### #",
                "# # # # # #       # #",
                "# # #   # # #####   #",
                "# # ##### # #   #####",
                "#         #   #     #",
                "###################E#" };
char Maze2[14][22] =
        {
                "#o###################",
                "#     #      #    # #",
                "# ### # ###### ## # #",
                "# # #        # #  # #",
                "# # ### ######## ## #",
                "#     # # ##   #    #",
                "### # # # ## # # ####",
                "# # # # #    #      #",
                "# # # # # ######### #",
                "# # # # # #       # #",
                "# # #   # # #####   #",
                "# # ##### # #   #####",
                "#         #   #     #",
                "###################E#" };

stack<Player> s;
stack<Player> s2;
stack<Player> m;
Player player;

int main(){
    char c;
    bool goBack = false;
    int cnt = 1;
    while(player.x != EXIT_X && player.y != EXIT_Y){
        m.push(player);
        Maze[player.x][player.y] = 'o';
        Maze2[player.x][player.y] = 'o';
        cin >> c;
        system("clear");
        printMaze();

        if (!goBack) { // if not calculated before
            player.right = 0; player.left = 0; player.down = 0; player.up = 0;
            if (player.x<14 && Maze[player.x+1][player.y]!='#') player.right=1;
            if (player.x>0 && Maze[player.x-1][player.y]!='#') player.left=1;
            if (player.y<21 && Maze[player.x][player.y+1]!='#') player.down=1;
            if (player.y>0 && Maze[player.x][player.y-1]!='#') player.up=1;
        }else goBack = false;

        bool moved = true;
        Player past = player;
        if (player.down && player.camefrom != DOWN) {
            player.y++;
            player.camefrom = UP;
            past.down = 0;
        }
        else if (player.up && player.camefrom != UP) {
            player.y--;
            player.camefrom = DOWN;
            past.up = 0;
        }
        else if (player.left && player.camefrom != LEFT) {
            player.x--;
            player.camefrom = RIGHT;
            past.left = 0;
        }
        else if (player.right && player.camefrom != RIGHT) {
            player.x++;
            player.camefrom = LEFT;
            past.right = 0;
        }
        else moved = false;

        // cout << m.top().x << " " << m.top().y << endl;
        // cout << cnt << endl;
        bool check = false;
        int temp;

        if (player.x != EXIT_X || player.y != EXIT_Y) {
            if ( (player.down + player.up + player.right + player.left) > 2) {
                temp = cnt;
                cnt = 1;
                check = false;
                while(!s.empty()){
                    if(s.top().x == past.x && s.top().y == past.y){
                        moved = false;
                        check = true;
                    }
                    if(!check)
                        s2.push(s.top());
                    s.pop();
                }

                while(!s2.empty()){
                    s.push(s2.top());
                    s2.pop();
                }
                if(!check)
                    s.push(past); 
            }else{
                cnt++;
            }

            if (!moved) { // has to go back
                if ( !s.empty() ) {
                    player = s.top();
                    s.pop();
                    goBack = true;
                }
                int a = 0;
                while(cnt > 0 || (check && temp > 0)){
                    if(!(check && !a)){
                        Maze[m.top().x][m.top().y] = '#';
                        Maze2[m.top().x][m.top().y] = ' ';
                    }
                    a++;
                    // cout << m.top().x << " " << m.top().y << endl;
                    m.pop();
                    cnt--;
                    temp--;
                }
            }
        }
    }

    Maze[player.y][player.x] = 'o';
    Maze2[player.y][player.x] = 'o';
    printMaze();
    cout << "PATH found" << endl;
    printMaze2();
    return 0;
}

void printMaze(){
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 21; j++)
            cout << Maze[i][j];
        cout << endl;
    }
    cout << endl << endl;
}

void printMaze2(){
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 21; j++)
            cout << Maze2[i][j];
        cout << endl;
    }
    cout << endl << endl;
}