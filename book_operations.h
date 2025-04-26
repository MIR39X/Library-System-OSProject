#ifndef BOOK_OPERATIONS_H
#define BOOK_OPERATIONS_H

// Function declarations for book operations
void addBook();
void removeBook();
void borrowBook();
void logEvent(const char *event);
int checkIfBookExists(char *bookTitle);
void viewBookCatalog();

// Function declarations for member operations
void addMember();
void removeMember();
void viewMemberList();

#endif
