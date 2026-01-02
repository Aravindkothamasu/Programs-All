#include "../inc/Hash_Header.h"

int main() {
    FILE *fp;
    char buffer[CSV_MAX_LINE_LENGTH];
    char* value;
    int row = 0;
    int column = 0;

    // 1. Open the file in read mode
    fp = fopen(CSV_FILENAME, "r");
    if (!fp) {
        perror("Can't open file");
        return EXIT_FAILURE;
    }

    // 2. Read each line of the file
    while (fgets(buffer, CSV_MAX_LINE_LENGTH, fp)) {
        column = 0;
        row++;

        /*
        // Optional: Skip the header row (row 1)
        if (row == 1) {
            continue;
        }
        */

        // 3. Split the line into tokens using a comma as the delimiter
        value = strtok(buffer, ",");
        while (value) {
            // Process each value (e.g., print or store in a data structure)
            if (column == 0) {
                printf("Name: ");
            } else if (column == 1) {
                printf("\tAccount No.: ");
            } else if (column == 2) {
                printf("\tAmount: ");
            }
            printf("%s", value);

            // Move to the next token
            value = strtok(NULL, ",");
            column++;
        }
        printf("\n"); // Newline after processing all columns in a row
    }

    // 4. Close the file
    fclose(fp);
    return EXIT_SUCCESS;
}
