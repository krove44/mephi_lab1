#include "test.h"


void first_light_test() {
    printf("\n");
    printf("first_test:\n");
    vector_dict* sany = Create("i am kostia", get_char_type());
    assert(find("i", sany, 1, get_char_type()) == 0);
    assert(find("am", sany, 1, get_char_type()) == 2);
    assert(find("kostia", sany, 1, get_char_type()) == 5);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
};


void first_light_test_error() {
    printf("first_test_error:\n");
    vector_dict* sany = Create("я и костя", get_char_type());
    assert(find("петя", sany, -10, get_char_type()) == -1);
    assert(find("олег", sany, 1, get_char_type()) == -1);
    assert(find("костя", sany, 10000, get_char_type()) == -1);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
};


