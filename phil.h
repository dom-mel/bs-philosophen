#ifndef PHIL_H
#define PHIL

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define PHILO_NUM 5

void* philo(void *args);
void think(int num);
void eat(int num);
void philo_wait();

#endif
