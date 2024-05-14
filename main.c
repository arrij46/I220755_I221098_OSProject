#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <semaphore.h>
#include <pthread.h>
#include "global.h"
#include "player.h"
#include "ghost.h"
#include "stack.h"
#include "global.h"
#include "player.h"
#include "ghost.h"
#include "stack.h"

void *GhostFunction(void *arg);
void *inputhandling(void *arg);
void display();
void player_mov();
void keyboard(int key, int xx, int yy);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // Initialize food and maze structures
    Initialize();
    initPlayer(&p);
    GhostInit(g);
    srand(time(0));

    // init sema
    sem_init(&setting, 0, 1);
    sem_init(&writing, 0, 1);
    sem_init(&s1, 0, 1);

    sem_init(&key, 0, 2);
    sem_init(&permit, 0, 2);

    pthread_mutex_init(&ProducerConsumerMutex, NULL); // locked
    sem_init(&CigaretteSmoker,0,1);

    
    // lock the sema
    sem_wait(&writing); // no one can write
    sem_wait(&s1);

    // Initialize timeRemaining
    timeRemaining = powerUpDuration;
    SpeedBoostRemaining = SpeedBoostDuration;

    // Start the timer
    glutTimerFunc(1000, timer, 0); // Initial call after 1 second

    // Create threads for input handling and ghost behavior
    pthread_t playerInputThread;
    pthread_create(&playerInputThread, NULL, inputhandling, NULL);

    pthread_t playerGhostThread[4];
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&playerGhostThread[i], NULL, GhostFunction, (void *)&g[i]);
    }

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(950, 900);
    glutCreateWindow("Pac-Man Maze");

    initOpenGL();

    printf("Game begins\n");
    // glutReshapeFunc(reshape);

    sem_post(&s1);
    sem_post(&writing); // unlock sema open to write

    glutDisplayFunc(display);

    glutMainLoop();
    // glutDestroyMenu();

    return 0;
}

void player_mov()
{
    sleep(0.05);
    int tx = p.x, ty = p.y;
    if (current_direction == 1) // right
    {
        tx++;
    }
    if (current_direction == 2) // left
    {
        tx--;
    }
    if (current_direction == 3) // up
    {
        ty++;
    }
    if (current_direction == 4) // down
    {
        ty--;
    }

    WrapAround();

    if (!PlayerMazeCollision(tx, ty))
    {
        sem_wait(&writing);
        p.x = tx;
        p.y = ty;
        sem_post(&writing);
    }
    PlayerFoodCollision();

    pthread_mutex_lock(&ProducerConsumerMutex);
    PlayerGhostPelletCollision();
    pthread_mutex_unlock(&ProducerConsumerMutex);

    PlayerFruitCollision();
    PlayerGhostCollision();
    glutTimerFunc(5000, player_mov, 0);

}
// Function to handle keyboard input
void keyboard(int key, int xx, int yy)
{
    //printf("User Interface thread\n");
    int tx = p.x, ty = p.y;
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        tx += 1; // Move square right
        current_direction = 1;

        current_direction = 1;

        break;
    case GLUT_KEY_LEFT:
        tx -= 1; // Move square left
        current_direction = 2;

        current_direction = 2;

        break;
    case GLUT_KEY_UP:
        ty += 1; // Move square up
        current_direction = 3;

        current_direction = 3;

        break;
    case GLUT_KEY_DOWN:
        ty -= 1; // Move square down
        current_direction = 4;

        current_direction = 4;

        break;
    }
    // printf("key: %d\n", key);
    if (!PlayerMazeCollision(tx, ty))
        // printf("key: %d\n", key);
        if (!PlayerMazeCollision(tx, ty))
        {
            sem_wait(&writing);
            p.x = tx;
            p.y = ty;
            sem_post(&writing);
        }
    WrapAround();
    pthread_mutex_lock(&ProducerConsumerMutex);
    //consumer
    PlayerGhostPelletCollision();
    PlayerGhostCollision();
    pthread_mutex_unlock(&ProducerConsumerMutex);
    PlayerFoodCollision();

    PlayerFruitCollision();
    for(int i=0; i<4; i++)
    if (g[i].isfreeze)
        PlayerEatsGhost(&g[i]);
    //player_mov();
    // score'//lives //food collision // ghost collision
}
void *inputhandling(void *arg)
{
    while (1)
    {
        // printf("UI THREAD RUNNING------------------------------\n");
        glutSpecialFunc(keyboard); // Register keyboard function
        sleep(1);
    }
}
void *GhostFunction(void *arg)
{
    ghost *g1 = (ghost *)arg;
    // printf("ghost thread runningg\n");
    while (1)
    {
        // sem_wait(&write);
        printf("ghost %d has entered \n", g1->id);
        if (g1->status == 0)
        {
            pick_key(g1);
            printf("ghost %d has picked \n", g1->id);
        }
        else
            while (MoveGhost(g1))
                ; // runs until the ghost alive
    }
    printf("GHOST THREAD exiting\n");
    return NULL;
}
// Function to display the maze and player on the screen
void display()
{
    // printf("Game THREAD RUNNING\n");
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    drawMaze(); // Draw the Pac-Man maze

    drawFood();
    drawSpeedBoost();

    // Producer
    pthread_mutex_lock(&ProducerConsumerMutex);

    
    drawPellet();
    drawGhost();
    pthread_mutex_unlock(&ProducerConsumerMutex);

    //drawGhost();

    // to prevent unnecessaty function calls
    if (fruit_loc[0].check != 1 || fruit_loc[1].check != 1 || fruit_loc[2].check != 1 || fruit_loc[3].check != 1)
        drawFruit();

    displayPlayer(); // Draw the player
    char scoreStr[20];
    sprintf(scoreStr, "%d", p.score); // Convert score to string
    renderText(2.0f, 33.0, "Score: ", scoreStr);
    sprintf(scoreStr, "%d", p.lives);             // Convert score to string
    renderText(22.0f, 33.0, "Lives: ", scoreStr); // Draw the player
    glutSwapBuffers();                            // Swap the buffers
    glutPostRedisplay();
}
