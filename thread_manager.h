// thread_manager.h
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <pthread.h>
#include <semaphore.h>

extern pthread_mutex_t mutex; // Declare the mutex globally

// Declarations for reader and writer threads
extern sem_t rw_mutex;

extern pthread_t readers[5];
extern pthread_t writers[2];

// Reader and writer thread functions
void* reader_thread(void* arg);
void* writer_thread(void* arg);

#endif
