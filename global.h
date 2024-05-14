#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <semaphore.h>
#include <pthread.h>

#define MAZE_WIDTH 27
#define MAZE_HEIGHT 35
#define CELL_SIZE 1
#define MAX_SIZE 1000      // for stack
#define TIMER_INTERVAL 200 // delay for ghost movement

// STRUCTURE DEFINATIONS

typedef struct
{
    int x, y;
} Coordinate;

typedef struct
{
    Coordinate List[MAX_SIZE];
    int top;
} Stack;

typedef struct
{
    float x;
    float y;
    float speed;
    int lives;
    int score;

} Player;

typedef struct
{
    float x;
    float y;
    int speed;
    Stack Path;
    int id;
    int status;   // to keep track if the ghost can leave the house or not
    int isfreeze; // to check if ghost can be eaten by the player
} ghost;

typedef struct
{
    float x;
    float y;
    int check;
} fruit;

Coordinate Pellet[2] = {{2, 7}, {23, 19}};

// GLOBAL VARIABLES

int current_direction = 0;
Player p;

ghost g[4];

Coordinate FC[555]; // food coordinates
Coordinate MC[309];
pthread_mutex_t mut;

fruit fruit_loc[4] = {{3, 8, 0}, {23, 8, 0}, {5, 25, 0}, {21, 25, 0}};

//  sema
sem_t writing, setting;
int readers = 0;
sem_t s1;
sem_t key, permit;

int powerUpDuration = 20; // Duration of power-up in seconds
int timeRemaining;

// MAZE (1 for wall)
int maze[32][27] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// Functions
void Initialize()
{
    int k = 0, l = 0;
    for (int c = 0; c < 27; c++) // col major
    {
        for (int j = 0; j < 32; j++)
        {
            if (maze[j][c] == 0)
            {
                // store the maze coordinates
                MC[k].x = c;
                MC[k].y = j;
                k++;
            }
            else
            {
                // store the food coordinates
                FC[l].x = c;
                FC[l].y = j;
                // to make sure there is no food in place of a fruit

                if ((FC[l].x == 3 && FC[l].y == 8) || (FC[l].x == 23 && FC[l].y == 8) || (FC[l].x == 5 && FC[l].y == 25) || (FC[l].x == 21 && FC[l].y == 25))
                {
                    FC[l].x = -1;
                    FC[l].y = -1;
                }
                l++;
            }
        }
    }
    // printf("MAZE total COORDINATES %d \n",k);
    // printf("FOOD total COORDINATES %d \n",l);
}

// Function to draw the Pac-Man maze && Food
void drawFood()
{
    for (int i = 0; i < 555; i++)
    {
        if (FC[i].x != -1)
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
    for (int i = 0; i < 309; i++)
    {
        glBegin(GL_LINE_LOOP);
        glVertex2i(MC[i].x, MC[i].y);
        glVertex2i(MC[i].x, (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), MC[i].y);
        glEnd();
    }
}

// different color maze
/*void drawMaze()
{
    // Set color to gray for the inner area
    glColor3f(0.0f, 0.0f, 0.15f);

    // Loop through the maze array and draw filled rectangles for inner area
    for (int i = 0; i < 309; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2i(MC[i].x, MC[i].y);
        glVertex2i(MC[i].x, (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), MC[i].y);
        glEnd();
    }

    // Set color to white for outer walls
    glColor3f(0.0f, 0.0f, 1.0f);

    // Loop through the maze array and draw outer walls where necessary
    for (int i = 0; i < 309; i++)
    {
        // Draw outer walls where maze cells are walls
        glBegin(GL_LINE_LOOP);
        glVertex2i(MC[i].x, MC[i].y);
        glVertex2i(MC[i].x, (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), (MC[i].y + 1));
        glVertex2i((MC[i].x + 1), MC[i].y);
        glEnd();
    }
}
*/
void drawFruit()
{
    for (int i = 0; i < 4; i++)
    {

        if (fruit_loc[i].x != -1)
        {
            glColor3f(0.98f, 0.5f, 0.45f);                                    // Set color to red
            glPushMatrix();                                                   // Save the current matrix
            glTranslatef(fruit_loc[i].x + 0.5f, fruit_loc[i].y + 0.5f, 0.0f); // Translate to the center of the cell
            glutSolidSphere(0.4f, 10, 10);                                    // Draw a wireframe sphere with radius 0.1
            glPopMatrix();                                                    // Restore the previous matrix
            glColor3f(0.0f, 0.0f, 1.0f);
        }
    }
}



void drawPellet()
{
    for (int i = 0; i < 2; i++)
    {
        if (Pellet[i].x != -1)
        {
            glColor3f(0.71f, 0.49f, 0.86f);                             // Set color to red
            glPushMatrix();                                             // Save the current matrix
            glTranslatef(Pellet[i].x + 0.5f, Pellet[i].y + 0.5f, 0.0f); // Translate to the center of the cell
            glutSolidSphere(0.3f, 20, 20);                              // Draw a wireframe sphere with radius 0.1
            glPopMatrix();                                              // Restore the previous matrix
            glColor3f(0.71f, 0.49f, 0.86f);
        }
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

void renderText(float x, float y, const char *text, char *sc)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    glRasterPos2f(x, y);         // Set the position for rendering text
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text); // Render each character
        text++;                                                 // Move to the next character
    }
    while (*sc)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *sc); // Render each character
        sc++;                                                 // Move to the next character
    }
    // printf("score: %d", p.score);
}

// Timer
void timer()
{
    if (g[0].isfreeze)
    {
        // Decrement time remaining
        timeRemaining--;
        // printf("Time dec....\n");

        if (timeRemaining <= 0)
        {
            // Power-up duration expired
            for (int i = 0; i < 4; i++)
                g[i].isfreeze = 0;
            timeRemaining = powerUpDuration; // Reset time remaining
        }
    }
    // function calls itself every 1s
    glutTimerFunc(1000, timer, 0);
}

/*
// color for ghost pellets
//(0.98f, 0.5f, 0.45f)
    Black: (0.0f, 0.0f, 0.0f)
    White: (1.0f, 1.0f, 1.0f)
    Red: (1.0f, 0.0f, 0.0f)
    Green: (0.0f, 1.0f, 0.0f)
    Blue: (0.0f, 0.0f, 1.0f)
    Yellow: (1.0f, 1.0f, 0.0f)
    Cyan: (0.0f, 1.0f, 1.0f)
    Magenta: (1.0f, 0.0f, 1.0f)
    Gray: You can create various shades of gray
    Orange: (1.0f, 0.5f, 0.0f)
    Pink: (1.0f, 0.75f, 0.8f)
    Purple: (0.5f, 0.0f, 0.5f)
    Lime Green: (0.75f, 1.0f, 0.0f)
    Teal: (0.0f, 0.5f, 0.5f)
    Sky Blue: (0.53f, 0.81f, 0.98f)
    Salmon: (0.98f, 0.5f, 0.45f)
    Lavender: (0.71f, 0.49f, 0.86f)
    Turquoise: (0.25f, 0.88f, 0.82f)
    Gold: (1.0f, 0.84f, 0.0f)
    Silver: (0.75f, 0.75f, 0.75f)
    Brown: (0.65f, 0.16f, 0.16f)
    Beige: (0.96f, 0.96f, 0.86f)
    Navy Blue: (0.0f, 0.0f, 0.5f)
    Maroon: (0.5f, 0.0f, 0.0f)
    Olive: (0.5f, 0.5f, 0.0f)
    Indigo: (0.29f, 0.0f, 0.51f)
    Slate Gray: (0.44f, 0.5f, 0.56f)
    Hot Pink: (1.0f, 0.41f, 0.71f)
    Chartreuse: (0.5f, 1.0f, 0.0f)
*/
#endif


// color for ghost pellets
//(0.98f, 0.5f, 0.45f)
/*
    Black: (0.0f, 0.0f, 0.0f)
    White: (1.0f, 1.0f, 1.0f)
    Red: (1.0f, 0.0f, 0.0f)
    Green: (0.0f, 1.0f, 0.0f)
    Blue: (0.0f, 0.0f, 1.0f)
    Yellow: (1.0f, 1.0f, 0.0f)
    Cyan: (0.0f, 1.0f, 1.0f)
    Magenta: (1.0f, 0.0f, 1.0f)
    Gray: You can create various shades of gray
    Orange: (1.0f, 0.5f, 0.0f)
    Pink: (1.0f, 0.75f, 0.8f)
    Purple: (0.5f, 0.0f, 0.5f)
    Lime Green: (0.75f, 1.0f, 0.0f)
    Teal: (0.0f, 0.5f, 0.5f)
    Sky Blue: (0.53f, 0.81f, 0.98f)
    Salmon: (0.98f, 0.5f, 0.45f)
    Lavender: (0.71f, 0.49f, 0.86f)
    Turquoise: (0.25f, 0.88f, 0.82f)
    Gold: (1.0f, 0.84f, 0.0f)
    Silver: (0.75f, 0.75f, 0.75f)
    Brown: (0.65f, 0.16f, 0.16f)
    Beige: (0.96f, 0.96f, 0.86f)
    Navy Blue: (0.0f, 0.0f, 0.5f)
    Maroon: (0.5f, 0.0f, 0.0f)
    Olive: (0.5f, 0.5f, 0.0f)
    Indigo: (0.29f, 0.0f, 0.51f)
    Slate Gray: (0.44f, 0.5f, 0.56f)
    Hot Pink: (1.0f, 0.41f, 0.71f)
    Chartreuse: (0.5f, 1.0f, 0.0f)
*/