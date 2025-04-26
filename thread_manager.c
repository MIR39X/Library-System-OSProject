#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "thread_manager.h"

// Define the global variables (mutex, rw_mutex, readers, writers)
pthread_t readers[5];
pthread_t writers[2];
sem_t rw_mutex;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for controlling access to shared resource

// Function to handle reader threads
void *reader_thread(void *arg) {
    // Reader thread logic (borrow/view books)
    sem_wait(&rw_mutex);  // Wait for a writer to finish
    pthread_mutex_lock(&mutex);

    printf("Reader thread: Viewing book catalog...\n");
    viewBookCatalog();  // This will print the catalog

    pthread_mutex_unlock(&mutex);
    sem_post(&rw_mutex);  // Allow other readers or writers

    return NULL;
}

// Function to handle writer threads
void *writer_thread(void *arg) {
    // Writer thread logic (add/remove books)
    sem_wait(&rw_mutex);  // Block other readers and writers
    pthread_mutex_lock(&mutex);

    // Simulate adding/removing a book
    printf("Writer thread: Adding/removing book...\n");
    addBook();  // This could be a function like addBook, removeBook, etc.

    pthread_mutex_unlock(&mutex);
    sem_post(&rw_mutex);  // Allow other readers or writers

    return NULL;
}
