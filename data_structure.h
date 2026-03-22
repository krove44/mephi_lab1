#pragma once

#include "Error.h"
#include "type/type_info.h"
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
    void* string_data;
    size_t len;
    vector_position el;
    type_info* type;

} dict;

typedef struct 
{
    dict* dict_data;
    size_t size;
    size_t capacity;

}vector_dict;



vector_dict* Create(void* v_str, type_info* type);

size_t find(void* v_find_string, vector_dict* vec, int n, type_info* type);

void free_data_struct(vector_dict* vec);

void print_info_about_error(Error type_error);


