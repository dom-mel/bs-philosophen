
#include "phil.h"

int *sticks;
sem_t *stickUse;
sem_t tableLock;

int main(int argc, char **argv) {
    pthread_t *threads;
    int i;
    threads = malloc(sizeof(pthread_t) * PHILO_NUM);
    sticks = malloc(sizeof(int) * PHILO_NUM);
    stickUse = malloc(sizeof(sem_t) * PHILO_NUM);
    sem_init(&tableLock, 0, PHILO_NUM -1);

    for (i=0; i<PHILO_NUM; ++i) {
        sticks[i] = 0;
        sem_init(&stickUse[i], 0, 1);
    }
    srand((unsigned int) time(NULL));

    for (i=0; i<PHILO_NUM; ++i) {
        int *argument = malloc(sizeof(int));
        *argument = i;
        pthread_create(&threads[i], NULL, philo, (void*) argument);
    }

    pthread_join(threads[0], NULL);

    return 0;
}

void* philo(void *args) {
    int *num = (int*) args;
    printf("%d hello\n", *num);
    while (1) {
        think(*num);
        eat(*num);
    }
    return NULL;
}

void think(int num) {
    printf("%d Thinking...\n", num);
    philo_wait();
}

void eat(int num) {

    printf("%d waiting for place on table\n", num);
    sem_wait(&tableLock);

    printf("%d taking left stick...\n", num);
    sem_wait(&stickUse[num]);

    printf("%d taking right stick...\n", num);
    sem_wait(&stickUse[(num + 1) % 5]);

    printf("%d eating...\n", num);
    philo_wait();

    sem_post(&stickUse[num]);
    sem_post(&stickUse[(num + 1) % PHILO_NUM]);
    sem_post(&tableLock);
}

void philo_wait() {
    sleep((rand() % 5)+1); // wait 1-5 sec
}
