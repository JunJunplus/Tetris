#include "mutex.h"

void mutex_init()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&cond_mutex, NULL);
    pthread_cond_init(&cond, NULL);
}