// 25k-3084 Q2:SUPERMARKET SYSTEM

#include <stdio.h>

void customerInfo(char name[], int cnic[]) {
    printf("Enter customer name: ");
    scanf("%s", name);
    printf("Enter CNIC (13 digits, no dashes): ");
    for (int i = 0; i < 13; i++) {
        scanf("%1d", &cnic[i]);
    }
}

void displayInventory(int codes[], int quantities[], int prices[], int size) {
    printf("\nProduct Code\tQuantity\tPrice per Product\n");
    for (int i = 0; i < size; i++) {
        printf("00%d\t\t%d\t\t%d\n", codes[i], quantities[i], prices[i]);
    }
}

void addToCart(int codes[], int quantities[], int prices[], int size, int cart[], int cartQty[], int *cartCount) {
    int code, qty, found = 0;
    printf("Enter product code to add: ");
    scanf("%d", &code);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < size; i++) {
        if (codes[i] == code) {
            found = 1;
            if (qty <= quantities[i]) {
                cart[*cartCount] = code;
                cartQty[*cartCount] = qty;
                (*cartCount)++;
                quantities[i] -= qty; // update inventory
                printf("Item added to cart successfully!\n");
            } else {
                printf("Not enough stock!\n");
            }
            break;
        }
    }
    if (!found) {
        printf("Product code not found!\n");
    }
}

float calculateTotal(int codes[], int prices[], int cart[], int cartQty[], int cartCount, int size) {
    float total = 0;
    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < size; j++) {
            if (cart[i] == codes[j]) {
                total += prices[j] * cartQty[i];
                break;
            }
        }
    }
    return total;
}

int checkPromo(char promo[]) {
    char valid[] = "Eid2025";
    int match = 1;
    for (int i = 0; promo[i] != '\0' || valid[i] != '\0'; i++) {
        if (promo[i] != valid[i]) {
            match = 0;
            break;
        }
    }
    return match;
}

void showInvoice(char name[], int cnic[], float total, int infoEntered) {
    if (!infoEntered) {
        printf("\nPlease enter customer information first!\n");
        return;
    }

    char ans[5], promo[20];
    float discount = 0, finalTotal = total;

    printf("Do you have a promocode? (yes/no): ");
    scanf("%s", ans);

    if (ans[0] == 'y' || ans[0] == 'Y') {
        printf("Enter promocode: ");
        scanf("%s", promo);
        if (checkPromo(promo)) {
            discount = total * 0.25;
            finalTotal = total - discount;
            printf("\nPromocode applied! 25%% discount granted.\n");
        } else {
            printf("\nInvalid promocode.\n");
        }
    }

    printf("\n---------- INVOICE ----------\n");
    printf("Customer Name: %s\n", name);
    printf("CNIC: ");
    for (int i = 0; i < 13; i++) {
        printf("%d", cnic[i]);
    }
    printf("\nTotal Bill (without discount): %.2f\n", total);
    printf("Discount: %.2f\n", discount);
    printf("Final Bill: %.2f\n", finalTotal);
    printf("-----------------------------\n");
}

int main() {
    int codes[4] = {1, 2, 3, 4};
    int quantities[4] = {50, 10, 20, 8};
    int prices[4] = {100, 200, 300, 150};
    int cart[10], cartQty[10], cartCount = 0;
    char name[100] = "N/A";
    int cnic[100] = {0};
    int choice;
    float total = 0;
    int infoEntered = 0; // flag to check if customer info entered

    while (1) {
        printf("\n--- Supermarket Menu ---\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerInfo(name, cnic);
                infoEntered = 1;
                break;

            case 2:
                displayInventory(codes, quantities, prices, 4);
                break;

            case 3:
                addToCart(codes, quantities, prices, 4, cart, cartQty, &cartCount);
                break;

            case 4:
                total = calculateTotal(codes, prices, cart, cartQty, cartCount, 4);
                printf("Total Bill (without discount): %.2f\n", total);
                break;

            case 5:
                total = calculateTotal(codes, prices, cart, cartQty, cartCount, 4);
                showInvoice(name, cnic, total, infoEntered);
                break;

            case 6:
                printf("Exiting system...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
