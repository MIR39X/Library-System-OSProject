#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "thread_manager.h"

int main() {
    // Initialize semaphore to allow multiple readers or single writer
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader_thread, NULL);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer_thread, NULL);
    }

    // Join threads (wait for all threads to finish)
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    return 0;
}
