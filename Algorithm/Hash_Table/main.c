#include "Hash_Header.h"

Person *Database[MAX_ARRAY_SIZE];

int generate_hash_index(Person *data) {
    // Later replace with another logic for hash_index
    return rand()%MAX_ARRAY_SIZE;
}

bool hash_insert_data(Person *data) {
    int hash_index = generate_hash_index(data);

    // check pointer
    if (data == NULL) return false;

    // check data
    if (data->Name == NULL) {
        printf("input data is NULL\n");
        return false;
    }

    if (Database[hash_index] == NULL) {
        Database[hash_index] = data;
    } else {
        // Need to add linked list entry
        printf("Hash index %02d entry is full\n", hash_index);
    }
    return true;
}

void print_hash_table() {
    int i;
    for ( i=0; i < MAX_ARRAY_SIZE; i++) {
        if (Database[i] == NULL) {
            printf("\t%02d, --------\n", i+1);
        } else {
            printf("\t%02d, ID: %d Name: %5s Grade: %d\n", i+1, Database[i]->Id, Database[i]->Name, Database[i]->Grade);
        }
    }
}

void main ()
{
    // print_hash_table();
    Person data1 = {.Id=123, .Name="abc", .Grade=123};
    Person data2 = {.Id=234, .Name="bcd", .Grade=234};
    Person data3 = {.Id=345, .Name="cde", .Grade=345};
    Person data4 = {.Id=456, .Name="def", .Grade=456};
    Person data5 = {.Id=567, .Name="efg", .Grade=567};
    Person data6 = {.Id=678, .Name="fgh", .Grade=678};
    Person data7 = {.Id=789, .Name="ghi", .Grade=789};
    Person data8 = {.Id=890, .Name="hij", .Grade=890};
    Person data9 = {.Id=901, .Name="ijk", .Grade=901};
    Person data10= {.Id=112, .Name="jkl", .Grade=112};
    Person data11= {.Id=123, .Name="klm", .Grade=123};
    Person data12= {.Id=234, .Name="lmn", .Grade=234};
    Person data13= {.Id=345, .Name="mno", .Grade=345};
    Person data14= {.Id=456, .Name="nop", .Grade=456};
    Person data15= {.Id=567, .Name="opq", .Grade=567};

    hash_insert_data(&data1);
    hash_insert_data(&data2);
    hash_insert_data(&data3);
    hash_insert_data(&data4);
    hash_insert_data(&data5);
    hash_insert_data(&data6);
    hash_insert_data(&data7);
    hash_insert_data(&data8);
    hash_insert_data(&data9);
    hash_insert_data(&data10);
    hash_insert_data(&data11);
    hash_insert_data(&data12);
    hash_insert_data(&data13);
    hash_insert_data(&data14);
    hash_insert_data(&data15);

    print_hash_table();
}
