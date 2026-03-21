#pragma once

#include "Error.h"
#include "typeinfo.h"
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
    size_t* data;
    size_t size;
    size_t capacity; 

} vector_len_string;

typedef struct 
{
    dict* dict_data;
    size_t size;
    size_t capacity;
    vector_len_string* vector_len_data;

}vector_dict;



vector_dict* Create(void* v_str);

size_t find(void* v_find_string, vector_dict* vec, int n, typeinfo t);

void free_data_struct(vector_dict* vec);

void print_info_about_error(Error type_error);