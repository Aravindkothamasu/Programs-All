#include "../inc/Hash_Header.h"

Person *Database[MAX_ARRAY_SIZE];

void add_data(int Id, char *Name, int Grade) {
    Person data = {0};

    data.Id=Id;
    strcpy(data.Name, Name);
    data.Grade=Grade;

    hash_insert_data(&data);
}

void main ()
{
    // print_hash_database();
    add_data(123, "abc", 123);
    add_data(234, "bcd", 234);
    add_data(345, "cde", 345);
    add_data(456, "def", 456);
    add_data(567, "efg", 567);
    add_data(678, "fgh", 678);
    add_data(789, "ghi", 789);
    add_data(890, "hij", 890);
    add_data(901, "ijk", 901);
    add_data(112, "jkl", 112);
    add_data(123, "klm", 123);
    add_data(234, "lmn", 234);
    add_data(345, "mno", 345);
    add_data(456, "nop", 456);
    add_data(567, "opq", 567);
    add_data(678, "pqr", 678);
    add_data(789, "qrs", 789);
    add_data(890, "rst", 890);
    add_data(901, "stu", 901);
    add_data(112, "tuv", 112);
    add_data(123, "uvw", 123);
    add_data(234, "vwx", 234);
    add_data(345, "wxy", 345);

    hash_print_database();

    if(hash_remove_data("vwx")){
        hash_remove_data("ijk");
        console_print("\n**** DELETED SUCCESSFULLY ****\n\n");
        hash_print_database();
    }

}
