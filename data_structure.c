#include "data_structure.h"

void create_new_element(void* s, size_t len, size_t position, vector_dict* vec, type_info* type) {
    //проверяю есть ли такое слово в мое словаре
    for (size_t i = 0; i < vec->size; i++){
        if (type->compare(vec->dict_data[i].string_data, s) == 0) {
            //если слово нашел значит добавлю его в вектор уже имеющихся позиций
            vector_position* element = &vec->dict_data[i].el;
            if (element->size < element->capacity_for_number){
                element->number_in_text[element->size] = position;
                element->size++;
                return;
            }
            //если места нехватило то увеличу и добавлю свою новую позицию
            element->capacity_for_number = element->capacity_for_number * 2;
            element->number_in_text = realloc(element->number_in_text, (element->capacity_for_number) * sizeof(size_t));
            element->number_in_text[element->size] = position;
            element->size++;
            return;
        }
    };
    //слово не нашел тогда добавлю словарь с этим словом
    //проверяю есть ли место в dict
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->dict_data = realloc(vec->dict_data, vec->capacity * sizeof(dict));
    };
    vec->size++;
    //создаю в словаре поисковое слово
    dict* just_dict = &vec->dict_data[vec->size - 1];
    just_dict->type = type;
    just_dict->string_data = type->clone(s, len);
    just_dict->len = len;
    //создаю новый массив элементов которых нет в словаре
    just_dict->el.size = 1;
    just_dict->el.capacity_for_number = 2;
    just_dict->el.number_in_text = (size_t*)malloc(just_dict->el.capacity_for_number * sizeof(size_t));
    just_dict->el.number_in_text[0] = position;
    return;
}


vector_dict* Create(void* str, type_info* type) {
    //делаю вектор словарей
    vector_dict* vector = (vector_dict*)malloc(sizeof(vector_dict));
    vector->size = 0;
    vector->capacity = 2;
    vector->dict_data = (dict*)malloc(vector->capacity * sizeof(dict));




    //начинаю бежать по веденной строке и добавлять словари в вектор, а в каждом словаре держу позицию этого слова.
    size_t len_str = type->get_len(str);
    size_t total_bytes = len_str * type->char_size;
    size_t current_byte = 0;
    size_t current_logical_id = 0;
    unsigned char* ptr = (unsigned char*) str;
    size_t start_id_logical = 0;
    size_t start_id_byte = 0;
    
    // for(size_t i = 0; i <= len_str; i++) {
    //     void* current_char_ptr = ptr + (i*(type->char_size));
    //     if (type->is_delim(current_char_ptr)) {
    //         size_t word_len = i - start_id;
    //         if (word_len > 0){
    //             void* word_start_ptr = ptr + (start_id * type->char_size);
    //             create_new_element(word_start_ptr, word_len, start_id, vector, type);
    //         }
    //         start_id = i + 1;
    //     }
    // }
    // return vector;

    while (current_byte < total_bytes) {
        void* current_ptr = ptr + current_byte;
        size_t step = type->get_next_size(current_ptr);
        if (type->is_delim(current_ptr)) {
            size_t word_len_bytes = current_byte - start_id_byte;
            if (word_len_bytes > 0){
                void* word_start_ptr = ptr + start_id_byte;
                create_new_element(word_start_ptr, word_len_bytes, start_id_logical, vector, type);
                start_id_byte = current_byte + type->char_size;
                start_id_logical = current_logical_id + 1;
            }

        }
        current_byte += step;
        current_logical_id++;
    }
    if (start_id_byte < total_bytes) {
        size_t word_len_bytes = total_bytes - start_id_byte;
        void* word_start_ptr = ptr + start_id_byte;
        create_new_element(word_start_ptr, word_len_bytes, start_id_logical, vector, type);
    }
    return vector;
};

int find(void* find_string, vector_dict* vec, int n, type_info* type) {
    if (n < 1){
        print_info_about_error(BAD_ARGUMENT);
        return -1;
    }
    for (size_t i = 0; i < vec->size; i++){
        if (type->compare(find_string, vec->dict_data[i].string_data) == 0){
                if (n > vec->dict_data[i].el.size){
                    print_info_about_error(STRING_WITHOUT_POS);
                    return -1;
                }
                print_info_about_error(ALL_OK);
                return vec->dict_data[i].el.number_in_text[n-1];
            };
        };
    print_info_about_error(STRING_NOWHERE);
    return -1;
};

void free_data_struct(vector_dict* vec) {
    for (size_t i = 0; i < vec->size; i++) {
        free(vec->dict_data[i].el.number_in_text);
        vec->dict_data[i].type->free_data((vec->dict_data[i].string_data));
    }
    free(vec->dict_data);
    free(vec);
}


void print_info_about_error(Error type_error) {
    if (type_error == ALL_OK) {
        printf("ALL_OK\n");
        return;
    }
    if (type_error == BAD_ARGUMENT) {
        printf("BAD_ARGUMENT\n");
        return;
    }
    if (type_error == STRING_WITHOUT_POS) {
        printf("STRING_WITHOUT_POS\n");
        return;
    }
    if (type_error == STRING_NOWHERE){
        printf("STRING_NOWHERE\n");
        return;
    }
    
}