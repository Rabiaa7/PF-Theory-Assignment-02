//25k-3084 (IESCO)
#include <stdio.h>

void updateSector(int rows, int cols, int grid[rows][cols], int row, int col, int flag, int set);
void querySector(int rows, int cols, int grid[rows][cols], int row, int col);
void runDiagnostic(int rows, int cols, int grid[rows][cols]);

int main() {
    int rows, cols;
    printf("Enter number of rows in grid: ");
    scanf("%d", &rows);
    printf("Enter number of columns in grid: ");
    scanf("%d", &cols);

    int grid[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = 0;

    int choice, row, col, flag, set;

    do {
        printf("\n--- IESCO Power Grid Monitoring System ---\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter sector coordinates (row col): ");
                scanf("%d %d", &row, &col);
                if (row < 0 || row >= rows || col < 0 || col >= cols) {
                    printf("Invalid coordinates!\n");
                    break;
                }
                printf("Select flag to modify:\n");
                printf("0 - Power Status\n1 - Overload Warning\n2 - Maintenance Required\n");
                scanf("%d", &flag);
                printf("Enter 1 to SET or 0 to CLEAR this flag: ");
                scanf("%d", &set);
                updateSector(rows, cols, grid, row, col, flag, set);
                break;

            case 2:
                printf("Enter sector coordinates (row col): ");
                scanf("%d %d", &row, &col);
                if (row < 0 || row >= rows || col < 0 || col >= cols) {
                    printf("Invalid coordinates!\n");
                    break;
                }
                querySector(rows, cols, grid, row, col);
                break;

            case 3:
                runDiagnostic(rows, cols, grid);
                break;

            case 4:
                printf("Exiting system...\n");
                break;

            default:
                printf("Invalid option!\n");
        }

    } while (choice != 4);

    return 0;
}

void updateSector(int rows, int cols, int grid[rows][cols], int row, int col, int flag, int set) {
    if (set)
        grid[row][col] = grid[row][col] | (1 << flag);
    else
        grid[row][col] = grid[row][col] & ~(1 << flag);

    printf("Sector [%d][%d] updated successfully.\n", row, col);
}

void querySector(int rows, int cols, int grid[rows][cols], int row, int col) {
    int status = grid[row][col];
    printf("\n--- Sector [%d][%d] Status ---\n", row, col);
    printf("Power Status: %s\n", (status & (1 << 0)) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (status & (1 << 1)) ? "YES" : "NO");
    printf("Maintenance Required: %s\n", (status & (1 << 2)) ? "YES" : "NO");
}

void runDiagnostic(int rows, int cols, int grid[rows][cols]) {
    int overloaded = 0, maintenance = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] & (1 << 1))
                overloaded++;
            if (grid[i][j] & (1 << 2))
                maintenance++;
        }
    }

    printf("\n--- System Diagnostic Report ---\n");
    printf("Total Overloaded Sectors: %d\n", overloaded);
    printf("Total Sectors Requiring Maintenance: %d\n", maintenance);
}
