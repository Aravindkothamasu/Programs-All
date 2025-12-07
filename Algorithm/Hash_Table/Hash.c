#include "Hash_Header.h"

extern Person *Database[MAX_ARRAY_SIZE];

// Generate index form input data.
int hash_generate_index(char *NameStr) {
    int i, hash_index = 0;

    // For now only considering Name element as encoding, later u can add more.

    // Need: Name field to be mandatory to encode and to generate index value.
    if(NameStr == "") return -1;

    for (i=0; i < strlen(NameStr); i++) {
        hash_index += NameStr[i];
    }
    return hash_index%MAX_ARRAY_SIZE;
}

// Find required data from data structure
// Return data.
int hash_search_data(Person *data, char *NameStr) {
    int hash_index = hash_generate_index(NameStr);;
    Person *dataPtr = NULL;

    if (hash_index == -1){
        console_print("unable to get hash index value\n");
        return -1;
    }

    if(Database[hash_index] == NULL) 
        return -1;
    else {
        // Data Found.
        /*
        DataPtr = Database[Index];
        for( ;DataPtr->Next; DataPtr=DataPtr->Next) {
            if(Database[Iterator])
        }
            */
        if (true==hash_copy_contents(Database[hash_index], data))
            return 0;
    }
    return -1;
}

// Insert Data into database
bool hash_insert_data(Person *data) {
    int hash_index = hash_generate_index(data->Name);

    // check for index pointer
    if (hash_index == -1){
        console_print("unable to get hash index value\n");
        return false;
    }

    // check pointer
    if (data == NULL) 
        return false;

    // check data
    if (data->Name == NULL) {
        console_print("input data is NULL\n");
        return false;
    }

    if (Database[hash_index] == NULL) {
        Database[hash_index] = data;
    } else {
        // Need to add linked list entry
        console_print("Hash index %02d entry is full\n", hash_index);
    }
    return true;
}

// Remove Data from Database
bool hash_remove_data(char *NameStr) {
    int hash_index = hash_generate_index(NameStr);

    if (Database[hash_index]==NULL) return false;

    if(!strcmp(Database[hash_index]->Name, NameStr))
        Database[hash_index] = NULL;
    else {
        console_print("Unable to remove ")
    }


    return true;
}

// Copy all structure components data from src to dest.
bool hash_copy_contents(Person *SrcData, Person *DestData) {
    // return if data is NULL.
    if (SrcData==NULL && DestData==NULL) return false;

    DestData->Id    = SrcData->Id;
    strncpy(DestData->Name, SrcData->Name, strlen(SrcData->Name));
    DestData->Grade = SrcData->Grade;
    // FIXME: if any new elements are added, please update me.
    return true;
}

// Print database.
void hash_print_database() {
    int i;
    for ( i=ITERATOR_START_INDX; i < ITERATOR_END_INDX; i++) {
        if (Database[i] == NULL) {
            printf("\t%02d, --------\n", i+1);
        } else {
            printf("\t%02d, ID: %d Name: %5s Grade: %d\n", i+1, Database[i]->Id, Database[i]->Name, Database[i]->Grade);
        }
    }
}
