// thread_manager.h
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <pthread.h>
#include <semaphore.h>

// Declare global variables (do not define them here)
extern pthread_t readers[5];
extern pthread_t writers[2];
extern sem_t rw_mutex;
extern pthread_mutex_t mutex;


// Reader and writer thread functions
void* reader_thread(void* arg);
void* writer_thread(void* arg);

// Declare functions defined in book_operations.c
void viewBookCatalog();  // Declare the function to view the book catalog
void addBook();  // Declare the function to add a book

#endif
