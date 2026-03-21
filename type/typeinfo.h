#pragma once

typedef struct 
{
    // функция для сравнения двух слов
    int (*compare) (const void* item_in_dict, const void* word);
    
    //функция для получения длины
    size_t (*get_len) (const void* data);
    
    //функция для освобождения памяти  
    void (*free_data)(void* data);

    //функция для вывода
    void (*print)(const void* data);

} type_info;

