#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include "book_operations.h"

//-- ANSI color codes for terminal output--//
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"  
//-- ANSI color codes for terminal output--//



//--Functions--//
void logEvent(const char *event) {
    FILE *logFile = fopen("log.txt", "a");
    if (logFile == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(logFile, "%02d-%02d-%04d %02d:%02d:%02d - %s\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec, event);

    fclose(logFile);  
}

int checkIfBookExists(char *bookTitle) {
    FILE *inFile;
    char line[256];
    int bookFound = 0;

    
    inFile = fopen("books.txt", "r");
    if (inFile == NULL) {
        printf(RED"Error opening books file!\n"RESET);
        return 0; 
    }

  
    while (fgets(line, sizeof(line), inFile)) {
        if (strstr(line, bookTitle)) {
            bookFound = 1;
            break;
        }
    }

    fclose(inFile);
    return bookFound;
}


void addBook()
{
    char bookTitle[100], bookAuthor[100], bookISBN[20];
    char event[200];

   
    FILE *outFile = fopen("books.txt", "a");
    if (outFile == NULL)
    {
        printf("Error opening books file!\n");
        return;
    }

    printf(RED"Enter Book Details:\n"RESET);
    printf("Title: ");
    scanf("%s", bookTitle);
    printf("Author: ");
    scanf("%s", bookAuthor);
    printf("ISBN: ");
    scanf("%s", bookISBN);
    snprintf(event, sizeof(event), "Librarian added the book '%s'", bookTitle);
    logEvent(event);

    
    fprintf(outFile, "Title: %s\n", bookTitle);
    fprintf(outFile, "Author: %s\n", bookAuthor);
    fprintf(outFile, "ISBN: %s\n", bookISBN);
    fprintf(outFile, "\n"); 
    fclose(outFile); 
    printf(RED"--Book Added Successfully--\n"RESET);
    sleep(1);
    system("clear");

}

void removeBook()
{
    char bookToRemove[100];
    FILE *inFile, *outFile;
    char line[256];
    int bookFound = 0;

  
    printf(RED"Enter the title of the book you want to remove: "RESET);
    getchar();
    fgets(bookToRemove, sizeof(bookToRemove), stdin);
    bookToRemove[strcspn(bookToRemove, "\n")] = 0; 

    inFile = fopen("books.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening books file!\n");
        return;
    }

   
    outFile = fopen("tempBooks.txt", "w");
    if (outFile == NULL)
    {
        printf("Error opening temporary file!\n");
        fclose(inFile);
        return;
    }

   
    while (fgets(line, sizeof(line), inFile))
    {
        if (strstr(line, bookToRemove))
        {
            
            for (int i = 0; i < 3; i++)
            {
                if (!fgets(line, sizeof(line), inFile))
                {
                    break;
                }
            }
            bookFound = 1;
        }
        else
        {
            fputs(line, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    if (!bookFound)
    {
        printf(RED"Book not found.\n"RESET);
        remove("tempBooks.txt");
    }
    else
    {
        remove("books.txt");
        rename("tempBooks.txt", "books.txt");
        printf("Book removed successfully.\n");

        
        char event[200];
        snprintf(event, sizeof(event), "Librarian removed the book '%s'", bookToRemove);
        logEvent(event);
        sleep(1);
        system("clear"); 
    }
}

void viewBookCatalog()
{
    printf("\n");
    FILE *inFile;
    char line[256];

    
    inFile = fopen("books.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening books file!\n");
        return;
    }

   
    system("clear");
    printf("\n");
    printf(RED"Library Book Catalog:\n"RESET);
    while (fgets(line, sizeof(line), inFile))
    {
      
        printf("%s", line);
    }

    fclose(inFile); 
    printf("\n");
    printf("\n");
    printf("\n");
}

void addMember()
{
    char memberName[100], memberID[50], memberContact[50];
    char event[200];

   
    FILE *outFile = fopen("members.txt", "a");
    if (outFile == NULL)
    {
        printf("Error opening members file!\n");
        return;
    }

   
    printf(RED"Enter Member Details:\n"RESET);
    printf("Name: ");
    scanf("%s", memberName);
    printf("ID: ");
    scanf("%s", memberID);
    printf("Contact: ");
    scanf("%s", memberContact);

   
    fprintf(outFile, "Name: %s\n", memberName);
    fprintf(outFile, "ID: %s\n", memberID);
    fprintf(outFile, "Contact: %s\n", memberContact);
    fprintf(outFile, "\n"); 

    snprintf(event, sizeof(event), "Librarian added a new member '%s'", memberName);
    logEvent(event);  

    fclose(outFile); 
    printf(RED"--Member Added Successfully--\n"RESET);
    sleep(1);
    system("clear");
}

void removeMember()
{
    char memberToRemove[50];
    FILE *inFile, *outFile;
    char line[256];
    int memberFound = 0;

    
    printf(RED"Enter the name of the member you want to remove: "RESET);
    getchar();
    fgets(memberToRemove, sizeof(memberToRemove), stdin);
    memberToRemove[strcspn(memberToRemove, "\n")] = 0; 

    
    inFile = fopen("members.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening members file!\n");
        return;
    }

    
    outFile = fopen("tempMembers.txt", "w");
    if (outFile == NULL)
    {
        printf("Error opening temporary file!\n");
        fclose(inFile);
        return;
    }

    
    while (fgets(line, sizeof(line), inFile))
    {
       
        if (strstr(line, memberToRemove))
        {
           
            for (int i = 0; i < 3; i++)
            {
                if (!fgets(line, sizeof(line), inFile))
                {
                    break;
                }
            }
            memberFound = 1;
        }
        else
        {
           
            fputs(line, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

   
    if (!memberFound)
    {
        printf("Member not found.\n");
        remove("tempMembers.txt");
        sleep(1);
        system("clear");
    }
    else
    {
       
        remove("members.txt");
        rename("tempMembers.txt", "members.txt");
        printf("Member removed successfully.\n");
    }
    char event[200];
    snprintf(event, sizeof(event), "Librarian removed member '%s'", memberToRemove);
    logEvent(event);
    sleep(1);
    system("clear"); 

}

void viewMemberList()
{
    FILE *inFile;
    char line[256];

    
    inFile = fopen("members.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening members file!\n");
        return;
    }

   
    sleep(1);
    system("clear");
    printf(RED"Library Members List:\n"RESET);
    while (fgets(line, sizeof(line), inFile))
    {
        
        printf("%s", line);
    }

    fclose(inFile); 
    printf("\n");
}

void borrowBook()
{
    char bookTitle[100];

   
    printf(RED"Enter the title of the book you want to borrow: "RESET);
    getchar(); 
    fgets(bookTitle, sizeof(bookTitle), stdin);
    bookTitle[strcspn(bookTitle, "\n")] = 0;

   
    if (checkIfBookExists(bookTitle))
    {
        printf("The book '%s' is available for borrowing.\n", bookTitle);

       
        char event[200];
        snprintf(event, sizeof(event), "Student borrowed the book '%s'", bookTitle);
        logEvent(event);
        sleep(1);
        system("clear");

    }
    else
    {
        printf("The book '%s' is not available in the catalog.\n", bookTitle);
    }
}
//--Functions--//
//--End of book_operations.c--//
