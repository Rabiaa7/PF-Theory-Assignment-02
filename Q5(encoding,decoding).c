//25K-3084(Encoding/Decoding)
#include <stdio.h>
#include <string.h>

void reverseString(char str[]) {
    int i, j;
    char temp;


    for (i = 0; str[i] != '\0'; i++);
    j = i - 1;

    for (i = 0; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void toggleBits(char *ch) {
    *ch = *ch ^ (1 << 1);
    *ch = *ch ^ (1 << 4);
}

void encodeMessage(char message[]) {
    int i;
    reverseString(message);

    for (i = 0; message[i] != '\0'; i++) {
        toggleBits(&message[i]);
    }
}

void decodeMessage(char message[]) {
    int i;

    for (i = 0; message[i] != '\0'; i++) {
        toggleBits(&message[i]);
    }

    reverseString(message);
}

int main() {
    int choice;
    char message[500];

    while (1) {
        printf("\n--- TCS Secure Message Tool ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            printf("\nEnter message to ENCODE: ");
            fgets(message, sizeof(message), stdin);

            // remove newline using strcspn
            message[strcspn(message, "\n")] = '\0';

            encodeMessage(message);
            printf("\nEncoded Message: %s\n", message);
        }
        else if (choice == 2) {
            printf("\nEnter message to DECODE: ");
            fgets(message, sizeof(message), stdin);

            // remove newline using strcspn
            message[strcspn(message, "\n")] = '\0';

            decodeMessage(message);
            printf("\nDecoded Message: %s\n", message);
        }
        else if (choice == 3) {
            printf("\nExiting program...\n");
            break;
        }
        else {
            printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

