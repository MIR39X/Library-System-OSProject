#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_operations.h"

// Function to add a new book to the library
void addBook() {
    char bookTitle[100], bookAuthor[100], bookISBN[20];
    
    // Open the books.txt file in append mode to add new books
    FILE *outFile = fopen("books.txt", "a");
    if (outFile == NULL) {
        printf("Error opening books file!\n");
        return;
    }

    // Prompt user for book details
    printf("Enter Book Details:\n");
    printf("Title: ");
    scanf("%s", bookTitle);
    printf("Author: ");
    scanf("%s", bookAuthor);
    printf("ISBN: ");
    scanf("%s", bookISBN);

    // Write book details to the file
    fprintf(outFile, "Title: %s\n", bookTitle);
    fprintf(outFile, "Author: %s\n", bookAuthor);
    fprintf(outFile, "ISBN: %s\n", bookISBN);
    fprintf(outFile, "\n");  // Add a blank line to separate books

    fclose(outFile);  // Close the file after adding the book
    printf("--Book Added Successfully--\n");
    // Implement the logic for adding a book here
}

// Function to remove a book from the library
void removeBook() {
    char bookToRemove[100];
    FILE *inFile, *outFile;
    char line[256];
    int bookFound = 0;

    // Ask for the title of the book to be removed
    printf("Enter the title of the book you want to remove: ");
    getchar();  // To clear the newline character left by previous input
    fgets(bookToRemove, sizeof(bookToRemove), stdin);
    bookToRemove[strcspn(bookToRemove, "\n")] = 0;  // Remove the trailing newline

    // Open the books.txt file for reading
    inFile = fopen("books.txt", "r");
    if (inFile == NULL) {
        printf("Error opening books file!\n");
        return;
    }

    // Create a temporary file to write the updated content
    outFile = fopen("tempBooks.txt", "w");
    if (outFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(inFile);
        return;
    }

    // Read the original file line by line
    while (fgets(line, sizeof(line), inFile)) {
        // If the current line contains the book title to remove, skip writing it to the temp file
        if (strstr(line, bookToRemove)) {
            // Skip the next 3 lines (to remove the entire book's details)
            for (int i = 0; i < 3; i++) {
                if (!fgets(line, sizeof(line), inFile)) {
                    break;
                }
            }
            bookFound = 1;
        } else {
            // Write the line to the temporary file
            fputs(line, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    // If the book was not found, display a message
    if (!bookFound) {
        printf("Book not found.\n");
        remove("tempBooks.txt");  // Delete the temporary file
    } else {
        // Delete the original file and rename the temporary file
        remove("books.txt");
        rename("tempBooks.txt", "books.txt");
        printf("Book removed successfully.\n");
    }
}

// Function to view the entire catalog of books
void viewBookCatalog() {
    printf("\n");
    FILE *inFile;
    char line[256];

    // Open the books.txt file for reading
    inFile = fopen("books.txt", "r");
    if (inFile == NULL) {
        printf("Error opening books file!\n");
        return;
    }

    // Display the book catalog
    printf("Library Book Catalog:\n");
    while (fgets(line, sizeof(line), inFile)) {
        // Print each line of the file (each book's detail)
        printf("%s", line);
    }

    fclose(inFile);  // Close the file after reading
    printf("\n");
    printf("\n");
    printf("\n");
}

// Function to add a new library member
void addMember() {
    char memberName[100], memberID[50], memberContact[50];

    // Open the members.txt file in append mode
    FILE *outFile = fopen("members.txt", "a");
    if (outFile == NULL) {
        printf("Error opening members file!\n");
        return;
    }

    // Prompt the user for member details
    printf("Enter Member Details:\n");
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
    fprintf(outFile, "\n");  // Add a blank line to separate members

    fclose(outFile);  // Close the file after adding the member
    printf("--Member Added Successfully--\n");
}

// Function to remove a library member
void removeMember() {
    char memberToRemove[50];
    FILE *inFile, *outFile;
    char line[256];
    int memberFound = 0;

    // Ask for the name of the member to be removed
    printf("Enter the name of the member you want to remove: ");
    getchar();  // To clear the newline character left by previous input
    fgets(memberToRemove, sizeof(memberToRemove), stdin);
    memberToRemove[strcspn(memberToRemove, "\n")] = 0;  // Remove the trailing newline

    // Open the members.txt file for reading
    inFile = fopen("members.txt", "r");
    if (inFile == NULL) {
        printf("Error opening members file!\n");
        return;
    }

    // Create a temporary file to write the updated content
    outFile = fopen("tempMembers.txt", "w");
    if (outFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(inFile);
        return;
    }

    // Read the original file line by line
    while (fgets(line, sizeof(line), inFile)) {
        // If the current line contains the member's name to remove, skip writing it to the temp file
        if (strstr(line, memberToRemove)) {
            // Skip the next 3 lines (to remove the entire member's details)
            for (int i = 0; i < 3; i++) {
                if (!fgets(line, sizeof(line), inFile)) {
                    break;
                }
            }
            memberFound = 1;
        } else {
            // Write the line to the temporary file
            fputs(line, outFile);
        }
    }

    fclose(inFile);
    fclose(outFile);

    // If the member was not found, display a message
    if (!memberFound) {
        printf("Member not found.\n");
        remove("tempMembers.txt");  // Delete the temporary file
    } else {
        // Delete the original file and rename the temporary file
        remove("members.txt");
        rename("tempMembers.txt", "members.txt");
        printf("Member removed successfully.\n");
    }
}

// Function to view the list of all library members
void viewMemberList() {
    FILE *inFile;
    char line[256];

    // Open the members.txt file for reading
    inFile = fopen("members.txt", "r");
    if (inFile == NULL) {
        printf("Error opening members file!\n");
        return;
    }

    // Display the list of members
    printf("Library Members List:\n");
    while (fgets(line, sizeof(line), inFile)) {
        // Print each line of the file (each member's detail)
        printf("%s", line);
    }

    fclose(inFile);  // Close the file after reading
    printf("\n");
}
