#pragma once

#include "Error.h"
#include "type_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct 
{
    size_t* number_in_text;
    size_t size;
    size_t capacity_for_number;

} vector_position; 


typedef struct
{
    char* string_data;
    size_t len;
    size_t capacity;
    vector_position el;

} dict;

typedef struct 
{
    dict* dict_data;
    size_t size;
    size_t capacity;

}vector_dict;


vector_dict* Create(const char* str);

Error find(const char* find_string, vector_dict* vec, size_t n);

void free_data_struct(vector_dict* vec);

