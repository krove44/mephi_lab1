#include "type_info.h"
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static size_t wchar_get_next_size(const void* data) {
    return sizeof(wchar_t);
}

static int wchar_compare(const void* a, const void* b) {
    return wcscmp((const wchar_t*)a, (const wchar_t*)b);
}

static size_t wchar_length(const void* a) {
    return wcslen((const wchar_t*)a);
}

static void* wchar_clone(const void* data, size_t l) {
    const wchar_t* s = (const wchar_t*)data;
    size_t len = l / sizeof(wchar_t);
    wchar_t* copy = malloc((len + 1) * sizeof(wchar_t));
    wmemcpy(copy, s, len);
    copy[len] = L'\0';
    return copy;
}

static void wchar_free(void* data) {
    if (data) {
        free(data);
    }
}

static bool wchar_is_delim(const void* data) {
    wchar_t p = *(const wchar_t*)data;
    return p == L' ' || p == L'\n' || p == L'\t';
}

static void wchar_print(const void* a) {
    wprintf(L"%ls", (const wchar_t*)a);
}

type_info wchar_type = {
    .get_next_size = wchar_get_next_size,
    .compare = wchar_compare,
    .get_len = wchar_length,
    .clone = wchar_clone,
    .is_delim = wchar_is_delim,
    .char_size = sizeof(wchar_t),
    .free_data = wchar_free,
    .print = wchar_print
};

type_info* get_wchar_type() {
    return &wchar_type;
}