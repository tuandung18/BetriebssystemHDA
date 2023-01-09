#ifndef __PHILOSOPHERS_ADVANCED_H__
#define __PHILOSOPHERS_ADVANCED_H__

#include <semaphore.h>

/* number of philosophers */
#define N 5

extern int pflag[N];  /* philosopher status flag; initially THINK */
#define THINKING 0
#define HUNGRY 	1
#define EATING 	2

/* DEFINE semaphores */
extern sem_t p[N]; /* per philosopher;	initially 0 */
extern sem_t mtx;  /* mutual exclusion; initially 1 */


// ****** Philosopher Utilities
void think(int i);

void eat(int i);

void test(int i);

void take_forks(int i);
 
void put_forks(int i);

// ****** Philosopher Thread Function
// The Signature (return type = paramater type = void*) 
// forced by POSIX Threads standard.
void *philosopher(void * threadId);

#endif
