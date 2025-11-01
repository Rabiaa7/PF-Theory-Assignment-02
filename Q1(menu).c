// 25k-3084 q1:liberty book store menu

#include <stdio.h>
void newBook(int isbns[], char titles[][50], float prices[],int quantities[], int *bookCount);
void sale(int isbns[], int quantities[], int bookCount);
void report(int isbns[], char titles[][50], float prices[],int quantities[], int bookCount);

int main() {
    int isbns[100];
    char titles[100][50];
    float prices[100];
    int quantities[100];
    int bookCount = 0;
    int choice;
    char ch;
    do{
    printf("choose an option: \n");
    printf("1.Add a new book \n 2.Process a sale \n 3.Generate a low-stock report \n");
    scanf("%d",&choice);

    switch (choice){
        case 1:
           newBook(isbns, titles, prices, quantities, &bookCount);
        break;
        case 2:
                sale(isbns, quantities, bookCount);
        break;
        case 3:
                report(isbns, titles, prices, quantities, bookCount);
        break;
        default:
                printf("Invalid choice \n");
        }

        printf("do you want to continue: y/n");
        scanf(" %c", &ch);

    }while(ch=='y'||ch=='Y');

    return 0;
}
void newBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount) {
    int isbn, i, duplicate = 0;
    if (*bookCount >= 100) {
        printf("space is full! Cannot add more books.\n");
        return;
    }

    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    for (i = 0; i < *bookCount; i++) {
        if (isbns[i] == isbn) {
            printf("Error: ISBN already exists.\n");
            duplicate = 1;
            break;
        }
    }

    if (!duplicate) {
        isbns[*bookCount] = isbn;
        printf("Enter title: ");
        scanf(" %[^\n]", titles[*bookCount]);  // reads spaces too
        printf("Enter price: ");
        scanf("%f", &prices[*bookCount]);
        printf("Enter quantity: ");
        scanf("%d", &quantities[*bookCount]);

        (*bookCount)++;
        printf("Book added successfully!\n");
    }
}

void sale(int isbns[], int quantities[], int bookCount) {
    int isbn, copies, i, found = 0;
    if (bookCount == 0) {
        printf("No books in inventory.\n");
        return;
    }

    printf("Enter ISBN of book sold: ");
    scanf("%d", &isbn);

    for (i = 0; i < bookCount; i++) {
        if (isbns[i] == isbn) {
            found = 1;
            printf("Enter number of copies sold: ");
            scanf("%d", &copies);

            if (copies <= quantities[i]) {
                quantities[i] -= copies;
                printf("Sale processed. Remaining quantity: %d\n", quantities[i]);
            } else {
                printf("Error: Not enough stock.\n");
            }
            break;
        }
    }

    if (!found)
        printf("Book not found.\n");
}

void report(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    int i, found = 0;
    if (bookCount == 0) {
        printf("No books in inventory.\n");
        return;
    }

    for (i = 0; i < bookCount; i++) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No low-stock books.\n");
}
