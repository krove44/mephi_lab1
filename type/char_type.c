#include "type_info.h"
#include <string.h>


size_t char_get_next_size(const void* data){
    return sizeof(char);
}

int char_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

size_t char_length(const void* a) {
    return strlen((const char*)a);
}

void* char_clone(const void* data, size_t l) {
    const char* s = (const char*)data;
    char* copy = malloc(l + 1);
    if (copy) {
        memcpy(copy, s, l);
        copy[l] = '\0';
    };
    return copy;
}

void char_free(void* data) {
    if (data) {
        free(data);
    }
}

bool char_is_delim(const void* data) {
    char p = *(const char*) data;
    return p == ' ' || p == '\n' || p == '\0';
}

void char_print(const void* data) {
    char p = *(const char*) data;
    printf("%c", p);
}

type_info char_type = {
    .get_next_size = char_get_next_size,
    .compare = char_compare,
    .get_len = char_length,
    .clone = char_clone,
    .is_delim = char_is_delim,
    .char_size = sizeof(char),
    .free_data = char_free,
    .print = char_print
};

type_info* get_char_type(){
    return &char_type;
}