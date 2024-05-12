#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


int ghost[4][2] = {{1, 0}, {2, 0}, {3, 0}, {4, 0}}; // 0 defines that ghost has not attained both key and permit
int key[2] = {0, 0};                                // 0-> available
int permit[2] = {0, 0};                             // 1-> taken

sem_t s1;
int pick_key(int num)
{
    sem_wait(&s1);
    int id;
    if (key[0] == 0)
    {
        id = 0;
        key[0] = 1;
        printf("ghost %d picks key 0\n", num);
    }
    else if (key[1] == 0)
    {
        id = 1;
        key[1] = 1;
        printf("ghost %d picks key 1\n", num);
    }
    sleep(3);
    sem_post(&s1);
    return id;
}
int pick_permit(int num)
{
    sem_wait(&s1);
    int id;
    if (permit[0] == 0)
    {
        id = 0;
        permit[0] = 1;
        ghost[num][1] = 1;
        printf("ghost %d picks permit 0\n", num);
    }
    else if (permit[1] == 0)
    {
        id = 1;
        permit[1] = 1;
        ghost[num][1] = 1;
        printf("ghost %d picks permit 1\n", num);
    }
    sleep(3);
    sem_post(&s1);
    return id;
}
void release_objects(int num, int kid, int pid)
{
    if (ghost[num][1] == 1)
    {
        ghost[num][1] = 0; // put down
        permit[pid]=0;
        key[kid]=0;
        printf("ghost %d had released both the objects\n", num);
    }
    // sleep(2);
}
void *ghostfunc(void *arg)
{

    int *num = (int *)arg;
    while (1)
    {
        int kid = pick_key(*num);
        int pid = pick_permit(*num);
        sleep(2);
        release_objects(*num, kid, pid);
    }
}

int main()
{
    sem_init(&s1, 0, 1);

    pthread_t p[4];
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&p[i], NULL, ghostfunc, (void *)&ghost[i]);
        sleep(2);
    }
    sem_destroy(&s1);
    pthread_exit(NULL);
    exit(0);
}