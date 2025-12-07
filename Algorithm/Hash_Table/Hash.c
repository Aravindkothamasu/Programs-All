#include "Hash_Header.h"

extern Person *Database[MAX_ARRAY_SIZE];
char   PrintBuf[500]={0};

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
bool hash_search_data(Person *data, char *NameStr) {            // TODO: Remove search data.
    int hash_index = hash_generate_index(NameStr);;
    Person *dataPtr = NULL;

    if (hash_index == -1){
        console_print("unable to get hash index value\n");
        return false;
    }

    if(Database[hash_index] == NULL) 
        return false;
    else {
        if (true==hash_copy_contents(Database[hash_index], data))
            return true;
    }
    return false;
}

// Insert Data into database
bool hash_insert_data(Person *data) {
    int hash_index = hash_generate_index(data->Name);
    Person *newDataPtr=NULL, *dataPtr=NULL;

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

    // loop to last struct, if data already exists.
    if (Database[hash_index]) {
        dataPtr=Database[hash_index];
        while(dataPtr->next) {
            dataPtr=dataPtr->next;
        }
    }
    
    newDataPtr = calloc(1, sizeof(Person));
    if (newDataPtr==NULL){
        console_print("unable to create dynamic memory\n");
        return false;
    }

    if(!hash_copy_contents(data, newDataPtr)) {
        console_print("Unable to copy contents\n");
        free(newDataPtr);
        return false;
    }

    // create links
    if (Database[hash_index]) {
        newDataPtr->prev = dataPtr;
        dataPtr->next    = newDataPtr;
    } else {
        Database[hash_index] = newDataPtr;
    }

    return true;
}

// Remove Data from Database
bool hash_remove_data(char *NameStr) {
    int hash_index = hash_generate_index(NameStr);
    Person *DataPtr=NULL;

    if (Database[hash_index]==NULL) return false;

    for(DataPtr=Database[hash_index];DataPtr;DataPtr=DataPtr->next) {
        if(!strcmp(DataPtr->Name, NameStr)) {
            if(DataPtr->next)
                DataPtr->next->prev = DataPtr->prev;
            if(DataPtr->prev)
                DataPtr->prev->next = DataPtr->next;

            free(DataPtr);
            return true;
        }
        
    }

    return false;
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
    Person *dataPtr=NULL;

    for ( i=ITERATOR_START_INDX; i < ITERATOR_END_INDX; i++) {
        if (Database[i] == NULL) {
            console_print("\t%02d, --------\n", i+1);
        } else {
            sprintf(PrintBuf,"\t%02d, Name: ", i+1);
            for(dataPtr=Database[i]; dataPtr; dataPtr=dataPtr->next) {
                sprintf(PrintBuf+strlen(PrintBuf), "- %s ", dataPtr->Name);
            }
            sprintf(PrintBuf+strlen(PrintBuf),"\n");

            console_print(PrintBuf);
        }
    }
}
