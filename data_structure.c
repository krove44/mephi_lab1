#include "data_structure.h"

void create_new_element(char* s, size_t len, size_t position, vector_dict* vec) {
    //проверяю есть ли такое слово в мое словаре
    for (size_t i = 0; i < vec->size; i++){
        if (strcmp(s, vec->dict_data[i].string_data) == 0) {
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
    vec->size++;
    //создаю в словаре поисковое слово
    dict* just_dict = &vec->dict_data[vec->size - 1];
    just_dict->string_data = s;
    just_dict->len = len;
    just_dict->capacity = len + 1;
    //создаю новый массив элементов которых нет в словаре
    just_dict->el.size = 1;
    just_dict->el.capacity_for_number = 2;
    just_dict->el.number_in_text = (size_t*)malloc(just_dict->el.capacity_for_number * sizeof(size_t));
    just_dict->el.number_in_text[0] = position;
}


vector_dict* Create(void* str, type_info* type) {
    //делаю вектор словарей
    vector_dict* vector = (vector_dict*)malloc(sizeof(vector_dict));
    vector->size = 0;
    vector->capacity = 2;
    vector->dict_data = (dict*)malloc(vector->capacity * sizeof(dict));
    //начинаю бежать по веденной строке и добавлять словари в вектор, а в каждом словаре держу позицию этого слова.
    size_t len_str = type->get_len(str);
    unsigned char* ptr = (unsigned char*) str;
    size_t start_id = 0;

    for(size_t i = 0; i <= len_str; i++) {
        void* current_char_ptr = ptr + (i*(type->char_size));
        if (type->is_delim(current_char_ptr)) {
            size_t word_len = i - start_id;
            if (word_len > 0){
                void* word_start_ptr = ptr + (start_id * type->char_size);
                create_new_element(word_start_ptr, word_len, start_id, vector, type);
            }
            start_id = i + 1;
        }
    }
    return vector;
};

size_t find(void* v_find_string, vector_dict* vec, int n, typeinfo type) {
    const char* find_string = (const char*)v_find_string;
    if (n < 0) {
        print_info_about_error(BAD_ARGUMENT);
        return -1;
    }
    if (type == first_type){
        for (size_t i = 0; i < vec->size; i++){
            if (strcmp(find_string, vec->dict_data[i].string_data) == 0){
                if (vec->dict_data[i].el.size <= n){
                    print_info_about_error(STRING_WITHOUT_POS);
                    return -1;
                };
                print_info_about_error(ALL_OK);
                return vec->dict_data[i].el.number_in_text[n];
            };
        };
        print_info_about_error(STRING_NOWHERE);
        return -1;
    };
    if (type == second_type) {
        if (vec->vector_len_data->size < n) {
            print_info_about_error(BAD_ARGUMENT);
            return -1;
        };
        for (size_t i = 0; i < vec->size; i++){
            if (strcmp(find_string, vec->dict_data[i].string_data) == 0){
                for(size_t j = 0; j < vec->dict_data[i].el.size; j++){
                    if(vec->dict_data[i].el.number_in_text[j] <= vec->vector_len_data->data[n] && (vec->dict_data[i].el.number_in_text[j] >= vec->vector_len_data->data[n-1])) {
                        print_info_about_error(ALL_OK);
                        return (vec->dict_data[i].el.number_in_text[j] - vec->vector_len_data->data[n-1]);
                    };
                }
                print_info_about_error(STRING_NOWHERE);
                return -1;
            };
        }
        
        print_info_about_error(STRING_NOWHERE);
        return -1;
    }
    
    
}

void free_data_struct(vector_dict* vec) {
    for (size_t i = 0; i < vec->size; i++) {
        free(vec->dict_data[i].el.number_in_text);
        free(vec->dict_data[i].string_data);
    }
    free(vec->dict_data);
    free(vec->vector_len_data->data);
    free(vec->vector_len_data);
    free(vec);
}

typeinfo get_first_type() {
    return first_type;
}

typeinfo get_second_type() {
    return second_type;
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