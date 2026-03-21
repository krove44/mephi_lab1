#pragma once
#include <stdbool.h>

typedef struct 
{
    // функция для сравнения двух слов
    int (*compare) (const void* item_in_dict, const void* word);
    
    //функция для получения длины
    size_t (*get_len) (const void* data);

    //функция для клонирования
    void* (*clone) (const void* data);

    //проверка на то что это делитель проблел, '0' или '\n'
    bool (*is_delim) (const void* data);

    //размер того с каким типом данных я работаю
    size_t char_size;
    
    //функция для освобождения памяти  
    void (*free_data)(void* data);

    //функция для вывода
    void (*print)(const void* data);

} type_info;

