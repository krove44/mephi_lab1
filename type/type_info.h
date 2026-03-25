#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    //функция для счета на сколько по байтово перемещаться
    size_t (*get_next_size)(const void* data);
    // функция для сравнения двух слов
    int (*compare) (const void* item_in_dict, const void* word);
    
    //функция для получения длины
    size_t (*get_len) (const void* data);

    //функция для клонирования
    void* (*clone) (const void* data, size_t l);

    //проверка на то что это делитель проблел или '\n'
    bool (*is_delim) (const void* data);

    //размер того с каким типом данных я работаю
    size_t char_size;
    
    //функция для освобождения памяти  
    void (*free_data)(void* data);

} type_info;


type_info* get_char_type();
type_info* get_wchar_type();
type_info* get_html_type();