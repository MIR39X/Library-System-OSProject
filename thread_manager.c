#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "thread_manager.h"

// Define the global variables
pthread_t readers[5];
pthread_t writers[2];
sem_t rw_mutex;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for controlling access to shared resource
int writer_waiting = 0;

// Function to handle reader threads
void *reader_thread(void *arg)
{

    // If a writer is waiting, the reader should wait
    while (writer_waiting)
    {
        sem_wait(&rw_mutex);
    }

    sem_wait(&rw_mutex);
    pthread_mutex_lock(&mutex);

    printf("Reader thread: Viewing book catalog...\n");
    viewBookCatalog();

    pthread_mutex_unlock(&mutex);
    sem_post(&rw_mutex);

    return NULL;
}

// Function to handle writer threads
void *writer_thread(void *arg)
{
    writer_waiting = 1;

    sem_wait(&rw_mutex);
    pthread_mutex_lock(&mutex);

    printf("Writer thread: Adding/removing book...\n");
    addBook();

    pthread_mutex_unlock(&mutex);
    sem_post(&rw_mutex);

    writer_waiting = 0;
    return NULL;
}
