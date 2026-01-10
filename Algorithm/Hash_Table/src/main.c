#include "../inc/Hash_Header.h"

#define CSV_FILENAME "./Test_Input.csv"

Person *Database[MAX_ARRAY_SIZE]={0};

void add_data(int Id, char *Name, int Grade) {
    Person data = {0};

    data.Id=Id;
    strcpy(data.Name, Name);
    data.Grade=Grade;

    hash_insert_data(&data);
}

void main ()
{
    clock_t start_time, end_time;
    double cpu_time_used;

#if 0
    hash_remove_data("klm");
    console_print("\n**** DELETED SUCCESSFULLY ****\n\n");
    hash_print_database();
#endif

    FILE *fp = CsvOpen(CSV_FILENAME);
    if (fp == NULL) {
        console_print("FILE OPENING FAILURE\n");
        return;
    }

    start_time = clock();
    Person Data = {0};
    while( CsvReadData(fp, &Data)) {
        hash_insert_data(&Data);
        bzero(&Data, sizeof(Person));

        if( 1 == CsvPosIsAtEnd(fp)) {
            CsvClose(fp);
            break;
        }
    }
    hash_count_nodes();

    Person Temp = {0};
    if (hash_get_data("Priya Shetty",  &Temp)) {
        hash_print_node(&Temp);
    } else {
        console_print("Node Data not avaliable for Name: %s\n", "zab");
    }
    end_time = clock();

    // Calculate the difference and convert to seconds
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    console_print("Execution time: %f seconds\n", cpu_time_used);

    return;
}
