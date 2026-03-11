#include "data_structure.h"

int main() {
    vector_dict* sany = Create("я петя и костя и я любою играть в майнкрафт");
    find("костя", sany, 0);
    free_data_struct(sany);
    return 0;
}