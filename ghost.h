#ifndef GHOST_H
#define GHOST_H


#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>

#include"global.h"
#include"player.h"
#include"stack.h"


//GHOST FUNCTIONS

void GhostInit(ghost *g)
{
    g->x = 18;
    g->y = 4;
    g->speed = 0;
    StackInit(&g->Path);
}

// Function to display the player on the screen
void displayGhost(ghost g1)
{
    // printf("Player Position: (%.2f, %.2f)\n", x, y);
    glColor3f(1.0f, 1.0f, 0.0f); // Red = 1.0, Green = 1.0, Blue = 0.0
    glBegin(GL_QUADS);
    glVertex2i(g1.x, g1.y);
    glVertex2i(g1.x, (g1.y + 1));
    glVertex2i((g1.x + 1), (g1.y + 1));
    glVertex2i((g1.x + 1), g1.y);
    glEnd();
}

int valid(int x, int y)
{
    if (x >= 0 && x < 27 && y >= 0 && y < 32)
        return 1;
    else
        return 0;
}

void SetPath(ghost *g1, int startX, int startY, int endX, int endY)
{
    int visited[32][21];

    // init
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 27; j++)
            if (maze[i][j] == 0)
                visited[i][j] = 1;
            else
                visited[i][j] = 0;
    }

    // cout << "19, 4 is wall" << !maze[4][19] << endl;
    // cout << "19, 4 is visited" << visited[4][19] << endl;

    // temp queue
    Stack TempQ;
    // init
    StackInit(&TempQ);

    // push start node
    push(&TempQ, g1->y, g1->x);
    visited[g1->y][g1->x] = 1;

    // parent array start null
    Pair parent[32][27];
    parent[g1->y][g1->x].x = -1;
    parent[g1->y][g1->x].y = -1;

    // up right left down
    int dx[] = {0, +1, -1, 0};
    int dy[] = {+1, 0, 0, -1};
    int curry, currx, nextx, nexty;

    while (!isEmpty(&TempQ))
    {
        currx = front(&TempQ).y;//18
        curry = front(&TempQ).x;//4

        pop(&TempQ);
        //printf("Current: (%d,%d)\n", currx, curry);
        for (int i = 0; i < 4; i++)
        { 
            nextx = currx + dx[i];//18  19  17  18
            nexty = curry + dy[i];//5   4    4   3

            if (valid(nextx, nexty) && !visited[nexty][nextx])
            {
                //printf("Valid: (%d,%d)\n", nextx, nexty);
                push(&TempQ, nexty, nextx);
                visited[nexty][nextx] = 1;
                parent[nexty][nextx].x = curry;
                parent[nexty][nextx].y = currx;
            }
            //else printf("Invalid: (%d,%d)\n", nextx, nexty); 
        }
        printf("\n");
    }
    // print parent
    /*for(int i=0; i<32; i++)
    {
        for(int j=0; j<27; j++)if(parent[i][j].x!=0)
        printf("(%d,%d)",parent[i][j].x,parent[i][j].y);
        printf("\n");
    }*/
    //printf("\n");
    currx = endY; // 1  current.first
    curry = endX; // 25

    g1->Path;
    while (currx != -1 && curry != -1)
    {
        //printf("  (%d,%d)  ", curry, currx);
        push(&g1->Path, curry, currx);
        currx = parent[currx][curry].x;
        curry = parent[currx][curry].y;
    }

}

void MoveGhost(ghost *g1)
{
    // if stack is empty
    if(isEmpty(&g1->Path))
    {
        int endx = 25;//rand()%24+1;
        int endy = 1;//rand()%30+2;
        SetPath(g1,g1->x, g1->y,endx, endy);
    }
    Pair temp;
    temp.x = front(&g1->Path).x;
    temp.y = front(&g1->Path).y;
    pop(&g1->Path);
    g1->x = temp.x;
    g1->y = temp.y;
}

void CheckPath(ghost *g1)
{
    
    if(isEmpty(&g1->Path))
    {
        int endx = rand()%24+1;
        int endy = rand()%30+2;
        SetPath(g1,g1->x, g1->y,endx, endy);
    }

}

#endif