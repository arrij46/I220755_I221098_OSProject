#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include"global.h"
#include"ghost.h"


//PLAYER FUNCTIONS

void displayPlayer()
{
        glColor3f(1.0f, 1.0f, 0.0f); // Red = 1.0, Green = 1.0, Blue = 0.0
        glPushMatrix();
        glTranslatef(p.x + 0.5f, p.y + 0.5f, 0.0f); // Translate to the center of the cell
        glutSolidSphere(0.5f, 12, 12);                       // Draw a wireframe sphere with radius 0.4
        glPopMatrix();
}
int PlayerFoodCollision()
{
    for (int i = 0; i < 553; i++)
    {
        if (FC[i].x == p.x && FC[i].y == p.y)
        {
            FC[i].x = -1;
            FC[i].y = -1;
            p.score++;
            return 1;
        }
    }
    return 0;
}

int PlayerMazeCollision(int x, int y)
{
    for (int i = 0; i < 311; i++)
    {
        if (x == MC[i].x && y == MC[i].y)
        {
            return 1;
        }
    }
    return 0;
}

void WrapAround()
{
    if (p.x < 0)
    {
        p.x = 26;
    }
    else if (p.x > 26)
    {
        p.x = 0;
    }
}

#endif 