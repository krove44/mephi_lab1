#include <locale.h>
#include <windows.h>
#include "test.h"


int main() {
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");
    first_light_test();
    first_light_test_error();
    return 0;
}