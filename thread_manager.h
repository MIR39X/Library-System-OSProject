
#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <pthread.h>
#include <semaphore.h>

// Declare global variables
extern pthread_t readers[5];
extern pthread_t writers[2];
extern sem_t rw_mutex;
extern pthread_mutex_t mutex;


// Reader and writer thread functions
void* reader_thread(void* arg);
void* writer_thread(void* arg);

void viewBookCatalog(); 
void addBook();  
void removeBook();
void borrowBook();
#endif
