#include "typeinfo.h"
#include <string.h>
#include <stdio.h>

static int char_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

static size_t char_length(const void* a) {
    return strlen((const char*)a);
}

static void* char_clone(const void* data) {
    const char* s = (const char*)data;
    char* copy = malloc(strlen(s) + 1);
    if (copy) strcpy(copy, s);
    return copy;
}

static bool char_is_delim(const void* data) {
    char p = *(const char*) data;
    return p == ' ' || p == '\n' || p == '\0';
}

static void char_print(const void* a) {
    printf("%s", (const char*)a);
}

type_info char_type = {
    .compare = char_compare,
    .get_len = char_length,
    .clone = char_clone,
    .is_delim = char_is_delim,
    .char_size = sizeof(char),
    .free_data = NULL,
    .print = char_print
};

type_info* get_char_type(){
    return &char_type;
}