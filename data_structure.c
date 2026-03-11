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
            //если места нехватило до увеличу и добавлю свою новую позицию
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


vector_dict* Create(const char* str) {
    vector_dict* vector_d = (vector_dict*)malloc(sizeof(vector_dict));
    vector_d->size = 0;
    vector_d->capacity = 2;
    vector_d->dict_data = (dict*)malloc(vector_d->capacity * sizeof(dict));
    

    size_t j = 0;
    size_t i = 0;
    size_t point = 0;
    size_t len_str = strlen(str);
    while (i <= len_str) {
        if (str[i] == ' ' || str[i] == '\0') {
            point = i;
            if ((point - j) > 0) {
                size_t len_new_word = point - j;
                char* new_word = malloc(len_new_word + 1);
                memcpy(new_word, &str[j], len_new_word);
                new_word[len_new_word] = '\0';

                while (i == ' ' && i <= len_str){
                    i++;
                }

                if(vector_d->size == vector_d->capacity) {
                    vector_d->capacity = 2*vector_d->capacity;
                    vector_d->dict_data = realloc(vector_d->dict_data, (vector_d->capacity) * sizeof(dict));
                }
                create_new_element(new_word, len_new_word, j, vector_d);
                j = point + 1;
            }
        }
        i++;
    }
    return vector_d;
};

Error find(const char* find_string, vector_dict* vec, size_t n) {
    for (size_t i = 0; i < vec->size; i++){
        if (strcmp(find_string, vec->dict_data[i].string_data) == 0){
            printf("%d", vec->dict_data[i].el.number_in_text[n]);
            return ALL_OK;
        };
    }
    printf("%d", 1234);
    return ALL_OK;
}

void free_data_struct(vector_dict* vec) {
    for (size_t i = 0; i < vec->size; i++) {
        free(vec->dict_data[i].el.number_in_text);
        free(vec->dict_data[i].string_data);
    }
    free(vec);
}