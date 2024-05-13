#ifndef GHOST_H
#define GHOST_H
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include "global.h"
#include "player.h"
#include "stack.h"

void SetPath(ghost *g1, int startX, int startY, int endX, int endY);

// GHOST FUNCTIONS

void GhostInit(ghost g[4])
{
    for (int i = 0; i < 4; i++)
    {
        g[i].y = 16;
        g[i].id = i;
        g[i].status = 0;
        g[i].isfreeze = 0;
    }
    g[0].x = 11;
    g[1].x = 12;
    g[2].x = 14;
    g[3].x = 15;
    SetPath(&g[0], g[0].x, g[0].y, 1, 1);
    SetPath(&g[1], g[1].x, g[1].y, 25, 30);
    SetPath(&g[2], g[2].x, g[2].y, 25, 1);
    SetPath(&g[3], g[3].x, g[3].y, 1, 30);
}

// Function to display the Ghost on the screen
void displayGhost(ghost *g1, float a, float b, float c)
{
    // printf("Ghost Position: (%.2f, %.2f)\n", x, y);
    glColor3f(a, b, c);
    glBegin(GL_QUADS);
    glVertex2i(g1->x, g1->y);
    glVertex2i(g1->x, (g1->y + 1));
    glVertex2i((g1->x + 1), (g1->y + 1));
    glVertex2i((g1->x + 1), g1->y);
    glEnd();
}

void drawGhost()
{
    if (g[0].isfreeze == 1)
    {
        for (int i = 0; i < 4; i++)
            displayGhost(&g[i], 0.53f, 0.81f, 0.98f);
    }
    else
    {
        displayGhost(&g[0], 1.0f, 0.41f, 0.71f); // hot pink
        displayGhost(&g[1], 0.5f, 0.0f, 0.0f);   // maroon 
        displayGhost(&g[2], 0.0f, 1.0f, 1.0f); // cyan:
        displayGhost(&g[3], 0.75f, 1.0f, 0.0f);   // lime green
    }
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

    // temp queue
    Stack TempQ;
    // init
    StackInit(&TempQ);

    // push start node
    push(&TempQ, g1->y, g1->x); // 3,1
    visited[startY][startX] = 1;

    // parent array start null
    Coordinate parent[32][27];
    parent[startY][startX].x = -1;
    parent[startY][startX].y = -1;

    // up right left down
    int dx[] = {0, +1, -1, 0};
    int dy[] = {+1, 0, 0, -1};
    int curry, currx, nextx, nexty;

    while (!isEmpty(&TempQ))
    {
        currx = front(&TempQ).y; // 1
        curry = front(&TempQ).x; // 3

        pop(&TempQ);
        // printf("Current: (%d,%d)\n", currx, curry);
        for (int i = 0; i < 4; i++)
        {
            nextx = currx + dx[i]; // 18  19  17  18
            nexty = curry + dy[i]; // 5   4    4   3

            if (valid(nextx, nexty) && !visited[nexty][nextx])
            {
                // printf("Valid: (%d,%d)\n", nextx, nexty);
                push(&TempQ, nexty, nextx);
                visited[nexty][nextx] = 1;
                parent[nexty][nextx].x = curry;
                parent[nexty][nextx].y = currx;
            }
            // else printf("Invalid: (%d,%d)\n", nextx, nexty);
        }
        // printf("\n");
    }

    // printf("\n");
    currx = endY; // 1  current.first
    curry = endX; // 25

    g1->Path;
    while (currx != -1 && curry != -1)
    {
        // printf("  (%d,%d)  ", curry, currx);
        push(&g1->Path, curry, currx);
        currx = parent[currx][curry].x;
        curry = parent[currx][curry].y;
    }
}

int Wall(int x, int y)
{
    if (maze[y][x] == 0) // wall present
        return 0;
    else
        return 1;
}

void CreatePath(ghost *g1)
{
    printf("Setting Path ");
    int endx = -1;
    int endy = -1;
    sleep(1); // so that random val
    do
    {
        srand(time(NULL));
        endx = rand() % 24 + 1;
        endy = rand() % 29 + 1;
    } while (!Wall(endx, endy));

    printf("endx: %d endy: %d\n", endx, endy);
    SetPath(g1, g1->x, g1->y, endx, endy);
}

void release_objects(int id)
{
    sem_post(&key);    // key++
    sem_post(&permit); // permit++
    printf("ghost %d has released key and permit \n", id);
}

void PlayerEatsGhost(ghost *g1)
{
    if ((p.x == g1->x && p.y == g1->y))
    {
        printf("Ghost %d ate you\n", g1->id);
        g1->status = 0;
        g1->x = 11 + g1->id; // sets to start position
        g1->y = 16;
        g1->Path.top = -1;
        release_objects(g1->id);
    }
}

int MoveGhost(ghost *g1)
{

    if (isEmpty(&g1->Path))
    {
        sem_wait(&setting);
        CreatePath(g1);
        sleep(1);
        sem_post(&setting);
    }

    Coordinate temp;
    temp.x = front(&g1->Path).x;
    temp.y = front(&g1->Path).y;

    sem_wait(&writing);
    g1->x = temp.x;
    g1->y = temp.y;
    sem_post(&writing);

    pop(&g1->Path);
    if (g1->isfreeze)
        PlayerEatsGhost(g1);
    sleep(1);
    return g1->status;
}

void pick_permit(ghost *g1)
{
    sem_wait(&permit); // permit--1
    printf("ghost %d has a permit \n", g1->id);
}

int pick_key(ghost *g1)
{
    // atomic permit key access
    sem_wait(&s1);

    sem_wait(&key); // key-- 0
    printf("ghost %d has a key \n", g1->id);

    pick_permit(g1); // right fork

    g1->status = 1;
    sem_post(&s1);

    return g1->id;
}

#endif