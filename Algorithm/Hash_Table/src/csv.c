#include "../inc/Hash_Header.h"

FILE *fp = NULL;
char tempBuff[CSV_MAX_LINE_LENGTH] = {0};

FILE * CsvOpen(char *filename) {
    // 1. Open the file in read mode
    fp = fopen(filename, "r");
    if (!fp) {
        perror("Can't open file");
        return NULL;
    }

    // Reading a line to ignore metadata from file.
    fgets(tempBuff, CSV_MAX_LINE_LENGTH, fp);
    return fp;
}

void CsvClose(FILE *fp) {
    fclose(fp);
    return;
}

int CsvPosIsAtEnd(FILE *fp) {
    long curr;
    long end;

    if (!fp)
        return -1;

    curr = ftell(fp);
    if (curr == -1L)
        return -1;

    if (fseek(fp, 0, SEEK_END) != 0)
        return -1;

    end = ftell(fp);
    if (end == -1L)
        return -1;

    /* restore position */
    fseek(fp, curr, SEEK_SET);

    return curr == end;
}

bool CsvReadData(FILE *fp, Person *DataPtr) {
    char buffer[CSV_MAX_LINE_LENGTH];
    char* value;
    int column = 0, posStatus = 0;

    // Check Input Data
    if (DataPtr == NULL)
        return false;

    // Check File pointer
    if (fp == NULL)
        return false;

    // check for pointer is at end or not
    posStatus = CsvPosIsAtEnd(fp);
    if (-1 == posStatus) {
        console_print("Error in reading file position\n");
        return false;
    } else if ( 1 == posStatus) {
        console_print("Reading of the file is completed, nothing else is remaining to read\n");
        return false;
    }

    // Reading a line.
    if (fgets(buffer, CSV_MAX_LINE_LENGTH, fp) == NULL) {
        console_print("Unable to read from file: %s\n", strerror(errno));
        return false;
    }

    // Parsing line.
    value = strtok(buffer, ",");
    while (value) {
        if (column == 0) {
            DataPtr->Id = atoi(value);
        } else if (column == 1) {
            strncpy(DataPtr->Name, value, MAX_CHAR);
        } else if (column == 2) {
            DataPtr->Grade = atoi(value);
        }

        // Move to the next token
        value = strtok(NULL, ",");
        column++;
    }
    return true;
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
