#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "book_operations.h"
#include "thread_manager.h"

#define WIDTH 80 
#define DEFAULT_WIDTH 80  
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"  

int choice;

int getTerminalWidth() {
    const char* cols = getenv("COLUMNS");
    if (cols != NULL) {
        return atoi(cols);  
    }
    return DEFAULT_WIDTH;  
}
void printCenteredBold(const char* str) {
    int len = strlen(str);
    int width = getTerminalWidth();
    int spaces = (width - len) / 2; 

    printf("\033[1m");

    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s\n", str);
}

void displayMenu()
{   
    printf("\n");
    printf(RED"1. Add Book\n"RESET);
    printf(RED"2. Remove Book\n"RESET);
    printf(RED"3. View Book Catalog\n"RESET);
    printf(RED"4. Add Member\n"RESET);
    printf(RED"5. Remove Member\n"RESET);
    printf(RED"6. View Member List\n"RESET);
    printf(RED"7. Borrow Book\n"RESET);
    printf(RED"8. Exit\n"RESET);
}
int main() {
    printCenteredBold("_______________________________________________________");
    printCenteredBold("|                                                     |");
    printCenteredBold("|              Library Management System              |");
    printCenteredBold("|                                                     |");
    printCenteredBold("_______________________________________________________");

    // Initialize mutex and semaphore
    // Initialize semaphore to allow multiple readers or a single writer
    sem_init(&rw_mutex, 0, 1);

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

       
        switch (choice) {
            case 1:
                // Create writer thread to add a book
                pthread_create(&writers[0], NULL, writer_thread, NULL);
                pthread_join(writers[0], NULL);
                break;

            case 2:
               /* // Create writer thread to remove a book
                pthread_create(&writers[1], NULL, writer_thread, NULL);
                pthread_join(writers[1], NULL);
                break;
                */
               removeBook();
                break;

            case 3:
                // Create reader threads to view the book catalog
                for (int i = 0; i < 5; i++) {
                    pthread_create(&readers[i], NULL, reader_thread, NULL);
                }
                for (int i = 0; i < 5; i++) {
                    pthread_join(readers[i], NULL);
                }
                break;
            case 4:
                addMember();
                break;

            case 5:
                removeMember();
                break;

            case 6:
                viewMemberList();
                break;

            case 7:
                borrowBook();
                break;

            case 8:
                printf("Exiting the system...\n");

                sem_destroy(&rw_mutex);  // Destroy the semaphore
                pthread_mutex_destroy(&mutex);  // Destroy the mutex
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
