#include "../inc/Hash_Header.h"

FILE *fp = NULL;

FILE * CsvOpen(char *filename) {
    // 1. Open the file in read mode
    fp = fopen(filename, "r");
    if (!fp) {
        perror("Can't open file");
        return NULL;
    }
    return fp;
}

void CsvReadValues(FILE *fp) {
    char buffer[CSV_MAX_LINE_LENGTH];
    char* value;
    int row = 0;
    int column = 0;

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
                printf("Id: ");
            } else if (column == 1) {
                printf("\tName: ");
            } else if (column == 2) {
                printf("\tGrade: ");
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
    return;
}
