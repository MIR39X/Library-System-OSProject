#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "thread_manager.h"

// Define the global variables (mutex, rw_mutex, readers, writers)
pthread_t readers[5];
pthread_t writers[2];
sem_t rw_mutex;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for controlling access to shared resource
int writer_waiting = 0;

// Function to handle reader threads
void *reader_thread(void *arg) {
    // Reader thread logic (borrow/view books)

    // If a writer is waiting, the reader should wait
    while (writer_waiting) {
        sem_wait(&rw_mutex);  // Wait for a writer to finish
    }

    sem_wait(&rw_mutex);  // Wait for a writer to finish (if no writer is waiting)
    pthread_mutex_lock(&mutex);  // Lock the mutex to read the catalog

    printf("Reader thread: Viewing book catalog...\n");
    viewBookCatalog();  // This will print the catalog

    pthread_mutex_unlock(&mutex);  // Release mutex after reading
    sem_post(&rw_mutex);  // Allow other readers or writers

    return NULL;
}

// Function to handle writer threads
void *writer_thread(void *arg) {
    writer_waiting = 1;  // Writer is waiting

    sem_wait(&rw_mutex);  // Block other readers and writers
    pthread_mutex_lock(&mutex);  // Lock mutex for exclusive writing

    // Simulate adding/removing a book
    printf("Writer thread: Adding/removing book...\n");
    addBook();  // This could be a function like addBook, removeBook, etc.

    pthread_mutex_unlock(&mutex);  // Release mutex after writing
    sem_post(&rw_mutex);  // Allow other readers or writers

    writer_waiting = 0;  // Writer is done, reset the flag
    return NULL;
}
