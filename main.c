#include "data_structure.h"
#include <assert.h>

void first_light_test() {
    printf("\n");
    printf("first_test:\n");
    vector_dict* sany = Create("я и костя");
    assert(find("я", sany, 0, get_first_type()) == 0);
    assert(find("и", sany, 0, get_first_type()) == 0);
    assert(find("костя", sany, 0, get_first_type()) == 0);
    assert(find("петя", sany, -1, get_first_type()) == 1);
    assert(find("петя", sany, 0, get_first_type()) == 2);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
};

void second_light_test() {
    printf("second_test:\n");
    vector_dict* sany = Create("я и костя\n зашли в магазин за продуктами\nэто круто");
    assert(find("и", sany, 1, get_second_type()) == 0);
    assert(find("и", sany, -2, get_second_type()) == 1);
    assert(find("продуктами", sany, 2, get_second_type()) == 0);
    assert(find("это", sany, 3, get_second_type()) == 0);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}

void big_first_type_test(){
    printf("big_first_type_test:\n");
    vector_dict* sany = Create("Лямбда-функция (лямбда-выражение) — это компактное представление анонимной функции (функции без имени), которое можно создавать прямо в коде, там где она нужна. Концепция пришла из лямбда-исчисления (математика), но в программировании стала незаменимым инструментом.");
    assert(find("Лямбда-функция", sany, 0, get_first_type()) == 0);
    assert(find("Лямбда-функция", sany, 1, get_first_type()) == 2); //отсуствует
    assert(find("программировании", sany, 0, get_first_type()) == 0);
    assert(find("стала", sany, 0, get_first_type()) == 0);
    assert(find("это", sany, 3, get_first_type()) == 2); //отсуствует
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}


void big_second_type_test(){
    printf("big_second_type_test:\n");
    vector_dict* sany = Create("У лукоморья дуб зелёный;\nЗлатая цепь на дубе том:\nИ днём и ночью кот учёный\nВсё ходит по цепи кругом.\n\nИдёт направо — песнь заводит,\nНалево — сказку говорит.\nТам чудеса: там леший бродит,\nРусалка на ветвях сидит.\n");
    assert(find("дуб", sany, 1, get_second_type()) == 0);
    assert(find("дубе", sany, 2, get_second_type()) == 0);
    assert(find("программировании", sany, 0, get_second_type()) == 2);//отсуствует
    assert(find("Налево", sany, 7, get_second_type()) == 0);
    assert(find("это", sany, 1000, get_second_type()) == 2); //отсуствует
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}



int main() {
    first_light_test();
    second_light_test();
    big_first_type_test();
    big_second_type_test();
    return 0;
}