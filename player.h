#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>

// Function to display the player on the screen
void displayPlayer()
{
    // printf("Player Position: (%.2f, %.2f)\n", x, y);
    glColor3f(1.0f, 1.0f, 0.0f); // Red = 1.0, Green = 1.0, Blue = 0.0
    glBegin(GL_QUADS);
    glVertex2i(p.x, p.y);
    glVertex2i(p.x, (p.y + 1));
    glVertex2i((p.x + 1), (p.y + 1));
    glVertex2i((p.x + 1), p.y);
    glEnd();
}
//comment added
int PlayerFoodCollision()
{
    for (int i = 0; i < 553; i++)
    {
        if (FC[i].x == p.x && FC[i].y == p.y)
        {
            FC[i].x = -1;
            FC[i].y = -1;
            p.score++;
            if (p.score == 10)
            {
                p.lives++;
                p.score = 0;
            }
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