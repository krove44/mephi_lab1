#include <locale.h>
#include <windows.h>
#include "test.h"


int main() {
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");
    first_light_test();
    first_light_test_error();
    second_light_test();
    second_light_test_erorr();
    big_first_type_test();
    big_first_type_test_erorr();
    big_second_type_test();
    big_second_type_test_erorr();
    return 0;
}