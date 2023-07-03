#include <pthread.h>

pthread_mutex_t mutex; //互斥锁
pthread_mutex_t cond_mutex; //互斥锁

pthread_cond_t cond;

pthread_t main_tid;

extern void mutex_init();