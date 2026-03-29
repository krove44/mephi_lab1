#include "type_info.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t html_get_next_size(const void* data) {
    const char* str = (const char*)data;
    if (*str == '&') {
        const char* str1 = str + sizeof(char);
        const char* flag = strchr(str1, '&');
        const char* end = strchr(str, ';');
        if (flag && flag < end) {
            return sizeof(char);
        }
        if (end && (end - str) < 7 && (end - str) > 1) {
            return (end - str) + 1;
        }
    }
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
    }
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

void html_print(const void* data) {
    char p = *(const char*)data;
    printf("%c", p);
}

type_info html_type = {
    .get_next_size = html_get_next_size,
    .compare = html_compare,
    .get_len = html_length,
    .clone = html_clone,
    .is_delim = html_is_delim,
    .char_size = sizeof(char),
    .free_data = html_free,
    .print = html_print
};

type_info* get_html_type() {
    return &html_type;
}
