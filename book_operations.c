#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include "book_operations.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"  

void logEvent(const char *event) {
    FILE *logFile = fopen("log.txt", "a");
    if (logFile == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    // Get the current time and format it
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(logFile, "%02d-%02d-%04d %02d:%02d:%02d - %s\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec, event);

    fclose(logFile);  // Close the log file
}

int checkIfBookExists(char *bookTitle) {
    FILE *inFile;
    char line[256];
    int bookFound = 0;

    // Open the books.txt file for reading
    inFile = fopen("books.txt", "r");
    if (inFile == NULL) {
        printf(RED"Error opening books file!\n"RESET);
        return 0;  // No books found
    }

    // Check if the book exists in the catalog
    while (fgets(line, sizeof(line), inFile)) {
        if (strstr(line, bookTitle)) {
            bookFound = 1;
            break;
        }
    }

    fclose(inFile);
    return bookFound;
}


// Function to add a new book to the library
void addBook()
{
    char bookTitle[100], bookAuthor[100], bookISBN[20];
    char event[200];

    // Open the books.txt file in append mode to add new books
    FILE *outFile = fopen("books.txt", "a");
    if (outFile == NULL)
    {
        printf("Error opening books file!\n");
        return;
    }

    // Prompt user for book details
    printf(RED"Enter Book Details:\n"RESET);
    printf("Title: ");
    scanf("%s", bookTitle);
    printf("Author: ");
    scanf("%s", bookAuthor);
    printf("ISBN: ");
    scanf("%s", bookISBN);
    snprintf(event, sizeof(event), "Librarian added the book '%s'", bookTitle);
    logEvent(event); // Log the event

    // Write book details to the file
    fprintf(outFile, "Title: %s\n", bookTitle);
    fprintf(outFile, "Author: %s\n", bookAuthor);
    fprintf(outFile, "ISBN: %s\n", bookISBN);
    fprintf(outFile, "\n"); // Add a blank line to separate books

    fclose(outFile); // Close the file after adding the book
    printf(RED"--Book Added Successfully--\n"RESET);
    sleep(1);
    system("clear");

}

// Function to remove a book from the library
void removeBook()
{
    char bookToRemove[100];
    FILE *inFile, *outFile;
    char line[256];
    int bookFound = 0;

    // Ask for the title of the book to be removed
    printf(RED"Enter the title of the book you want to remove: "RESET);
    getchar(); // To clear the newline character left by previous input
    fgets(bookToRemove, sizeof(bookToRemove), stdin);
    bookToRemove[strcspn(bookToRemove, "\n")] = 0; // Remove the trailing newline

    // Open the books.txt file for reading
    inFile = fopen("books.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening books file!\n");
        return;
    }

    // Create a temporary file to write the updated content
    outFile = fopen("tempBooks.txt", "w");
    if (outFile == NULL)
    {
        printf("Error opening temporary file!\n");
        fclose(inFile);
        return;
    }

    // Read the original file line by line
    while (fgets(line, sizeof(line), inFile))
    {
        if (strstr(line, bookToRemove))
        {
            // Skip the next 3 lines (to remove the entire book's details)
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

        // Log the event of removing the book
        char event[200];
        snprintf(event, sizeof(event), "Librarian removed the book '%s'", bookToRemove);
        logEvent(event);
        sleep(1);
        system("clear"); // Log the event
    }
}

// Function to view the entire catalog of books
void viewBookCatalog()
{
    printf("\n");
    FILE *inFile;
    char line[256];

    // Open the books.txt file for reading
    inFile = fopen("books.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening books file!\n");
        return;
    }

    // Display the book catalog
    system("clear");
    printf("\n");
    printf(RED"Library Book Catalog:\n"RESET);
    while (fgets(line, sizeof(line), inFile))
    {
        // Print each line of the file (each book's detail)
        printf("%s", line);
    }

    fclose(inFile); // Close the file after reading
    printf("\n");
    printf("\n");
    printf("\n");
}

// Function to add a new library member
void addMember()
{
    char memberName[100], memberID[50], memberContact[50];
    char event[200];

    // Open the members.txt file in append mode
    FILE *outFile = fopen("members.txt", "a");
    if (outFile == NULL)
    {
        printf("Error opening members file!\n");
        return;
    }

    // Prompt the user for member details
    printf(RED"Enter Member Details:\n"RESET);
    printf("Name: ");
    scanf("%s", memberName);
    printf("ID: ");
    scanf("%s", memberID);
    printf("Contact: ");
    scanf("%s", memberContact);

    // Write member details to the file
    fprintf(outFile, "Name: %s\n", memberName);
    fprintf(outFile, "ID: %s\n", memberID);
    fprintf(outFile, "Contact: %s\n", memberContact);
    fprintf(outFile, "\n"); // Add a blank line to separate members

    snprintf(event, sizeof(event), "Librarian added a new member '%s'", memberName);
    logEvent(event);  // Log the event


    fclose(outFile); // Close the file after adding the member
    printf(RED"--Member Added Successfully--\n"RESET);
    sleep(1);
    system("clear");
}

// Function to remove a library member
void removeMember()
{
    char memberToRemove[50];
    FILE *inFile, *outFile;
    char line[256];
    int memberFound = 0;

    // Ask for the name of the member to be removed
    printf(RED"Enter the name of the member you want to remove: "RESET);
    getchar(); // To clear the newline character left by previous input
    fgets(memberToRemove, sizeof(memberToRemove), stdin);
    memberToRemove[strcspn(memberToRemove, "\n")] = 0; // Remove the trailing newline

    // Open the members.txt file for reading
    inFile = fopen("members.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening members file!\n");
        return;
    }

    // Create a temporary file to write the updated content
    outFile = fopen("tempMembers.txt", "w");
    if (outFile == NULL)
    {
        printf("Error opening temporary file!\n");
        fclose(inFile);
        return;
    }

    // Read the original file line by line
    while (fgets(line, sizeof(line), inFile))
    {
        // If the current line contains the member's name to remove, skip writing it to the temp file
        if (strstr(line, memberToRemove))
        {
            // Skip the next 3 lines (to remove the entire member's details)
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
            // Write the line to the temporary file
            fputs(line, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    // If the member was not found, display a message
    if (!memberFound)
    {
        printf("Member not found.\n");
        remove("tempMembers.txt");
        sleep(1);
        system("clear"); // Delete the temporary file
    }
    else
    {
        // Delete the original file and rename the temporary file
        remove("members.txt");
        rename("tempMembers.txt", "members.txt");
        printf("Member removed successfully.\n");
    }
    char event[200];
    snprintf(event, sizeof(event), "Librarian removed member '%s'", memberToRemove);
    logEvent(event);
    sleep(1);
    system("clear");  // Log the event

}

// Function to view the list of all library members
void viewMemberList()
{
    FILE *inFile;
    char line[256];

    // Open the members.txt file for reading
    inFile = fopen("members.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening members file!\n");
        return;
    }

    // Display the list of members
    sleep(1);
    system("clear");
    printf(RED"Library Members List:\n"RESET);
    while (fgets(line, sizeof(line), inFile))
    {
        // Print each line of the file (each member's detail)
        printf("%s", line);
    }

    fclose(inFile); // Close the file after reading
    printf("\n");
}

void borrowBook()
{
    char bookTitle[100];

    // Ask for the title of the book to borrow
    printf(RED"Enter the title of the book you want to borrow: "RESET);
    getchar(); // To clear the newline character left by previous input
    fgets(bookTitle, sizeof(bookTitle), stdin);
    bookTitle[strcspn(bookTitle, "\n")] = 0; // Remove the trailing newline

    // Check if the book exists in the catalog
    if (checkIfBookExists(bookTitle))
    {
        printf("The book '%s' is available for borrowing.\n", bookTitle);

        // Log the borrowing action
        char event[200];
        snprintf(event, sizeof(event), "Student borrowed the book '%s'", bookTitle);
        logEvent(event);
        sleep(1);
        system("clear"); // Log the event

        // Proceed with borrowing (you can modify the book status here if necessary)
    }
    else
    {
        printf("The book '%s' is not available in the catalog.\n", bookTitle);
    }
}
