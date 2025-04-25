#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "book_operations.h"

// Mutex and semaphore for controlling access to the library
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
sem_t rw_mutex;

pthread_t readers[3];
pthread_t writers[2];

// Reader thread logic (students accessing the books)
void* reader_thread(void* arg) {
    sem_wait(&rw_mutex);  // Wait if writer is active
    pthread_mutex_lock(&mutex);  // Start reading

    // Reader logic to view book catalog
    viewBookCatalog();

    pthread_mutex_unlock(&mutex);  // Release lock after reading
    sem_post(&rw_mutex);  // Allow other readers or a writer

    return NULL;
}

// Writer thread logic (librarians updating the books)
void* writer_thread(void* arg) {
    sem_wait(&rw_mutex);  // Wait if any reader is active
    pthread_mutex_lock(&mutex);  // Start writing

    // Writer logic to add/remove books or members
    addBook();
    addMember();

    pthread_mutex_unlock(&mutex);  // Release lock after writing
    sem_post(&rw_mutex);  // Allow other threads to proceed

    return NULL;
}
