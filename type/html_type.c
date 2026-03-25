#include "type_info.h"
#include <string.h>
#include <stdlib.h>

size_t html_get_next_size(const void* data) {
    const char* str = (const char*)data;
    if (*str == '\0') {
        return 0;
    }
    if (*str == '&') {
        const char* end = strchr(str, ';');
        //максимум 10 байт
        if (end && (end - str) < 10) {
            return (end - str) + 1;
        }
    }
    //если ничего не нашли, то это обычный символ
    return sizeof(char);

}
int html_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);    
}


size_t html_length(const void* a) {
    return strlen((const char*)a);
}


void* html_clone(const void* data, size_t l) {
    const char* s = (const char*)data;
    char* copy = malloc(l + 1);
    if (copy) {
        memcpy(copy, s, l);
        copy[l] = '\0';
    };
    return copy;
}

void html_free(void* data) {
    if (data) {
        free(data);
    }
}

bool html_is_delim(const void* data) {
    char p = *(const char*) data;
    return p == ' ' || p == '\n';
}

type_info html_type = {
    .get_next_size = html_get_next_size,
    .compare = html_compare,
    .get_len = html_length,
    .clone = html_clone,
    .is_delim = html_is_delim,
    .char_size = sizeof(char),
    .free_data = html_free,
};



type_info* get_html_type(){
    return &html_type;
}

