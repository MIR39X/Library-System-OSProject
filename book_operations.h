#ifndef BOOK_OPERATIONS_H
#define BOOK_OPERATIONS_H
//--Book Operations-//
void addBook();
void removeBook();
void borrowBook();
void logEvent(const char *event);
int checkIfBookExists(char *bookTitle);
void viewBookCatalog();

//--Member Operations-//
void addMember();
void removeMember();
void viewMemberList();

#endif
