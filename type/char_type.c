#include "typeinfo.h"
#include <string.h>
#include <stdio.h>

static int char_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

static size_t char_length(const void* a) {
    return strlen((const char*)a);
}

static void char_print(const void* a) {
    printf("%s", (const char*)a);
}