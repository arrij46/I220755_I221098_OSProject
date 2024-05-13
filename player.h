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
void initPlayer(Player *p)
{
    p->x = 2;//why not 1 1 
    p->y = 2;
    p->lives = 3;
    p->score = 0;
}

void displayPlayer()
{
    printf("Player Position: (%.2f, %.2f)\n", p.x, p.y);
    glColor3f(1.0f, 1.0f, 0.0f); // Red = 1.0, Green = 1.0, Blue = 0.0
    glBegin(GL_QUADS);
    glVertex2i(p.x, p.y);
    glVertex2i(p.x, (p.y + 1));
    glVertex2i((p.x + 1), (p.y + 1));
    glVertex2i((p.x + 1), p.y);
    glEnd();
}
int PlayerFoodCollision()
{
    for (int i = 0; i < 555; i++)
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
int PlayerFruitCollision()
{
    for (int i = 0; i < 4; i++)
    {
        if (fruit_loc[i].x == p.x && fruit_loc[i].y == p.y)
        {
            fruit_loc[i].x = -1;
            fruit_loc[i].y = -1;
            fruit_loc[i].check=1;
            p.score+=5;
            return 1;
        }
    
    }
    return 0;
}
int PlayerMazeCollision(int x, int y)
{
    for (int i = 0; i < 309; i++)
    {
        if (x == MC[i].x && y == MC[i].y)
        {
            return 1;
        }
    }
    return 0;
}
int PlayerFruitCollision()
{
    for (int i = 0; i < 4; i++)
    {
        if (fruit_loc[i].x == p.x && fruit_loc[i].y == p.y)
        {
            fruit_loc[i].x = -1;
            fruit_loc[i].y = -1;
            fruit_loc[i].check=1;
            p.score+=5;
            return 1;
        }
    
    }
    return 0;
}
int PlayerGhostPelletCollision()
{
    for (int i = 0; i < 2; i++)
    {
        if (Pellet[i].x == p.x && Pellet[i].y == p.y)
        {
            Pellet[i].x = -1;
            Pellet[i].y = -1;
            for(int i=0; i<4; i++)
            {
                g[i].isfreeze=1;
            }
            printf("Pellet colllected\n");
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