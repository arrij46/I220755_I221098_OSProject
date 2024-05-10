#include <stdio.h>
#include<unistd.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <pthread.h>
#include"global.h"
#include"player.h"



// Function to handle keyboard input
void keyboard(int key, int xx, int yy)
{
    // printf("inside thread\n");
    int tx = p.x, ty = p.y;
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        tx += 1; // Move square right
        break;
    case GLUT_KEY_LEFT:
        tx -= 1; // Move square left
        break;
    case GLUT_KEY_UP:
        ty += 1; // Move square up
        break;
    case GLUT_KEY_DOWN:
        ty -= 1; // Move square down
        break;
    }
    if (!PlayerMazeCollision(tx,ty))
    {
        p.x = tx;
        p.y = ty;
    }
    WrapAround();
    PlayerFoodCollision();
    
    


//score'//lives //food collision // ghost collision
    glutPostRedisplay(); // Post a redisplay to update the screen
}

void *inputhandling(void *arg)
{
    while (1)
    {
        glutSpecialFunc(keyboard); // Register keyboard function
        sleep(1); // Sleep to reduce CPU usage
    }
}
// Function to draw the Pac-Man maze
void drawFood()
{
    for (int i = 0; i < 553; i++)
    {
        if(FC[i].x != -1)
        {
        glColor3f(1.0f, 0.65f, 0.0f); // Set color to orange for the sphere
        glPushMatrix();
        glTranslatef(FC[i].x + 0.5f, FC[i].y + 0.5f, 0.0f); // Translate to the center of the cell
        glutWireSphere(0.1f, 10, 10);                       // Draw a wireframe sphere with radius 0.4
        glPopMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        }
    }
}
void drawMaze()
{
    glColor3f(0.0f, 0.0f, 1.0f); // Set color to blue
    // Loop through the maze array and draw walls where necessary
    // bottom left
    for (int i = 0; i < 311; i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2i(MC[i].x, MC[i].y);
        glVertex2i(MC[i].x, (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), MC[i].y);
        glEnd();
    }
}

// Function to initialize OpenGL settings
void initOpenGL()
{
    glEnable(GL_DEPTH_TEST);              // Enable depth testing
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, MAZE_WIDTH * CELL_SIZE, 0, MAZE_HEIGHT * CELL_SIZE); // Set up a 2D orthographic projection
    glMatrixMode(GL_MODELVIEW);
}

// Function to display the maze and player on the screen
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    drawMaze();                                         // Draw the Pac-Man maze
    drawFood();
    displayPlayer();                                    // Draw the player
    glutSwapBuffers(); // Swap the buffers
}

void printSomething()
{
    // printf("main\n");
    glutPostRedisplay(); // Post a redisplay to update the screen

}


void Initialize()
{
    int k = 0, l = 0;
    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (maze[j][i] == 0)
            {
                // store the maze coordinates
                MC[k].x = i;
                MC[k].y = j;
                k++;
            }
            else
            {
                // store the food coordinates
                FC[l].x = i;
                FC[l].y = j;
                l++;
            }
        }
    }
    //printf("MAZE total COORDINATES %d \n",k);
    //printf("FOOD total COORDINATES %d \n",l);
}

int main(int argc, char **argv)
{
    // Initialize food and maze structures 
    Initialize();
    p.x=2;
    p.y=2;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(950, 900);
    glutCreateWindow("Pac-Man Maze");

    initOpenGL();
    
    // Create threads for input handling and ghost behavior
    pthread_t playerInputThread, ghostThread;
    pthread_create(&playerInputThread, NULL, inputhandling, NULL);
    glutPostRedisplay(); // Post a redisplay to update the screen
    //pthread_create(&ghostThread, NULL, check, NULL);

    glutDisplayFunc(display);
    //glutIdleFunc(printSomething);

    glutMainLoop();

    return 0;
}