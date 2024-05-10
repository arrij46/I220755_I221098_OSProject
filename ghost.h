#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include "global.h"
#include <iostream>
#include <queue>

using namespace std;

typedef struct
{
    int x;
    int y;
    int speed;
    queue<pair<int, int>> pathQ;

} ghost;

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
}

void Set(ghost g1)
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

    // push start
    g1.pathQ.push(pair(g1.x, g1.y));
    visited[g1.x][g1.y] = 1;

    while (!g1.pathQ.empty())
    {
        pair<int, int> v = g1.pathQ.front();
        g1.pathQ.pop();

        // up
        if (valid(g1.x, g1.y - 1))
            if (!visited[g1.x][g1.y - 1])
            {
            }
        // down
        if (valid(g1.x + 1, g1.y))
            if (!visited[g1.x + 1][g1.y])
            {
            }
        // left
        if (valid(g1.x, g1.y + 1))
            if (!visited[g1.x][g1.y + 1])
            {
            }
        // right
        if (valid(g1.x - 1, g1.y))
            if (!visited[g1.x - 1][g1.y])
            {
            }
    }
}