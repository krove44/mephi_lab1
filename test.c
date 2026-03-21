#include "test.h"


void first_light_test() {
    printf("\n");
    printf("first_test:\n");
    vector_dict* sany = Create("я и костя");
    assert(find("я", sany, 0, get_first_type()) == 0);
    assert(find("и", sany, 0, get_first_type()) == 3);
    assert(find("костя", sany, 0, get_first_type()) == 6);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
};


void first_light_test_error() {
    printf("first_test_error:\n");
    vector_dict* sany = Create("я и костя");
    assert(find("петя", sany, -10, get_first_type()) == -1);
    assert(find("олег", sany, 0, get_first_type()) == -1);
    assert(find("костя", sany, 10000, get_first_type()) == -1);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
};



void second_light_test() {
    printf("second_test:\n");
    vector_dict* sany = Create("я и костя\n зашли в магазин за продуктами\nэто круто");
    assert(find("и", sany, 1, get_second_type()) == 3);
    assert(find("продуктами", sany, 2, get_second_type()) == 35);
    printf("%d", find("это", sany, 3, get_second_type()));
    assert(find("это", sany, 3, get_second_type()) == 0);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}

void second_light_test_erorr() {
    printf("second_test_erorr:\n");
    vector_dict* sany = Create("я и костя\n зашли в магазин за продуктами\nэто круто");
    assert(find("и", sany, -2, get_second_type()) == -1);
    assert(find("и", sany, 2, get_second_type()) == -1);
    assert(find("зашли", sany, 4, get_second_type()) == -1);
    assert(find("заш", sany, 2, get_second_type()) == -1);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}


void big_first_type_test(){
    printf("big_first_type_test:\n");
    vector_dict* sany = Create("Лямбда-функция (лямбда-выражение) — это компактное представление анонимной функции (функции без имени), которое можно создавать прямо в коде, там где она нужна. Концепция пришла из лямбда-исчисления (математика), но в программировании стала незаменимым инструментом.");
    assert(find("Лямбда-функция", sany, 0, get_first_type()) == 0);
    assert(find("программировании", sany, 0, get_first_type()) == 396);
    assert(find("стала", sany, 0, get_first_type()) == 429);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}

void big_first_type_test_erorr() {
    printf("big_first_type_test_erorr:\n");
    vector_dict* sany = Create("Лямбда-функция (лямбда-выражение) — это компактное представление анонимной функции (функции без имени), которое можно создавать прямо в коде, там где она нужна. Концепция пришла из лямбда-исчисления (математика), но в программировании стала незаменимым инструментом.");
    assert(find("Лямбда-функция", sany, 1, get_first_type()) == -1); //отсуствует
    assert(find("это", sany, 3, get_first_type()) == -1); //отсуствует
    assert(find("fffffff", sany, -1, get_first_type()) == -1);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}


void big_second_type_test(){
    printf("big_second_type_test:\n");
    vector_dict* sany = Create("У лукоморья дуб зелёный;\nЗлатая цепь на дубе том:\nИ днём и ночью кот учёный\nВсё ходит по цепи кругом.\n\nИдёт направо — песнь заводит,\nНалево — сказку говорит.\nТам чудеса: там леший бродит,\nРусалка на ветвях сидит.\n");
    assert(find("дуб", sany, 1, get_second_type()) == 22);
    assert(find("дубе", sany, 2, get_second_type()) == 27);
    assert(find("Налево", sany, 7, get_second_type()) == 0);
    assert(find("И", sany, 3, get_second_type()) == 0);
    assert(find("леший", sany, 8, get_second_type()) == 28);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}

void big_second_type_test_erorr() {
    printf("big_second_type_test_erorr:\n");
    vector_dict* sany = Create("У лукоморья дуб зелёный;\nЗлатая цепь на дубе том:\nИ днём и ночью кот учёный\nВсё ходит по цепи кругом.\n\nИдёт направо — песнь заводит,\nНалево — сказку говорит.\nТам чудеса: там леший бродит,\nРусалка на ветвях сидит.\n");
    assert(find("программировании", sany, 0, get_second_type()) == -1);//отсуствует
    assert(find("это", sany, 1, get_second_type()) == -1); //отсуствует
    assert(find("ночь", sany, 3, get_second_type()) == -1);
    assert(find("кот", sany, 2, get_second_type()) == -1);
    assert(find("кот", sany, -1000, get_second_type()) == -1);
    free_data_struct(sany);
    printf("\n");
    printf("----------------------------\n");
    printf("\n");
}

