#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>

// Global variables for player position and size
float x = 2;
float y = 2;


// Function to display the player on the screen
void displayPlayer()
{ 
    // printf("Player Position: (%.2f, %.2f)\n", x, y);
    glColor3f(1.0f, 1.0f, 0.0f); // Red = 1.0, Green = 1.0, Blue = 0.0
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x, (y + 1));
    glVertex2i((x + 1), (y + 1));
    glVertex2i((x + 1), y);
    glEnd();
}

int checkCollisionFood()
{
    for (int i = 0; i < 553; i++)
    {
        if (FC[i].x == x && FC[i].y == y)
        {
            FC[i].x = -1;
            FC[i].y = -1;
            // score++;
            return 1;
        }
    }
    return 0;
}
int PlayerMazeCollision()
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