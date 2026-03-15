#include "data_structure.h"

int main() {
    vector_dict* sany = Create("я и костя\n");
    find("костя", sany, 1, get_second_type());
    free_data_struct(sany);
    return 0;
}