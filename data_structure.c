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


vector_dict* Create(void* v_str) {
    //привожу к чару
    const char* str = (const char*)v_str;
    vector_dict* vector_d = (vector_dict*)malloc(sizeof(vector_dict));
    vector_d->size = 0;
    vector_d->capacity = 2;
    vector_d->dict_data = (dict*)malloc(vector_d->capacity * sizeof(dict));
    
    //реализация массива с префикснами суммами индексов строк до '\n' для второго типа вызова find
    vector_d->vector_len_data = (vector_len_string*)malloc(sizeof(vector_len_string));
    vector_d->vector_len_data->size = 1;
    vector_d->vector_len_data->capacity = 2;
    vector_d->vector_len_data->data = (size_t*)malloc(vector_d->vector_len_data->capacity * sizeof(size_t));
    //у нулевой строки нулевое начало
    vector_d->vector_len_data->data[0] = 0;

    size_t j = 0;
    size_t i = 0;
    size_t point = 0;
    size_t len_str = strlen(str);
    while (i <= len_str) {
        if (str[i] == '\n') {
            if (vector_d->vector_len_data->size < vector_d->vector_len_data->capacity){
                vector_d->vector_len_data->data[vector_d->vector_len_data->size] = i + 1;
                vector_d->vector_len_data->size++; 
            }
            else{
                vector_d->vector_len_data->capacity *= 2;
                vector_d->vector_len_data->data = realloc(vector_d->vector_len_data->data, vector_d->vector_len_data->capacity * sizeof(size_t));
                vector_d->vector_len_data->data[vector_d->vector_len_data->size] = i + 1;
                vector_d->vector_len_data->size++;
            }
        };
        if (str[i] == ' ' || str[i] == '\0' || str[i] == '\n') {
            point = i;
            if ((point - j) > 0) {
                size_t len_new_word = point - j;
                char* new_word = malloc(len_new_word + 1);
                memcpy(new_word, &str[j], len_new_word);
                new_word[len_new_word] = '\0';

                while (str[i] == ' ' && i <= len_str){
                    i++;
                }

                if(vector_d->size == vector_d->capacity) {
                    vector_d->capacity = 2*vector_d->capacity;
                    vector_d->dict_data = realloc(vector_d->dict_data, (vector_d->capacity) * sizeof(dict));
                }
                create_new_element(new_word, len_new_word, j, vector_d); 
                free(new_word);
            }
            j = point + 1;
        }
        i++;
    }
    return vector_d;
};

Error find(void* v_find_string, vector_dict* vec, int n, typeinfo type) {
    const char* find_string = (const char*)v_find_string;
    if (n < 0) {
        return BAD_ARGUMENT;
    }
    if (type == first_type){
        for (size_t i = 0; i < vec->size; i++){
            if (strcmp(find_string, vec->dict_data[i].string_data) == 0){
                if (vec->dict_data[i].el.size <= n){
                    printf("Данное слово c такой позицией отсуствует!\n");
                    return STRING_NOWHERE;
                };
                printf("Позиция элемента в тексте: %d \n", vec->dict_data[i].el.number_in_text[n]);
                return ALL_OK;
            };
        };
        printf("В тексте нет такого слова! \n");
        return STRING_NOWHERE;
    };
    if (type == second_type) {
        if (vec->vector_len_data->size < n) {
            printf("Такой строки не существует! \n");
            return STRING_NOWHERE;
        };
        for (size_t i = 0; i < vec->size; i++){
            if (strcmp(find_string, vec->dict_data[i].string_data) == 0){
                for(size_t j = 0; j < vec->dict_data[i].el.size; j++){
                    if(vec->dict_data[i].el.number_in_text[j] <= vec->vector_len_data->data[n] && (vec->dict_data[i].el.number_in_text[j] >= vec->vector_len_data->data[n-1])) {
                        printf("Данное слово находиться в строке %d его индекс относительно строки: %d \n", n, (vec->dict_data[i].el.number_in_text[j] - vec->vector_len_data->data[n-1]));
                        return ALL_OK;
                    };
                }
                printf("В данной строке слово отсуствует! \n");
                return STRING_NOWHERE;
            };
        }
        printf("В тексте нет такого слова! \n");
        return STRING_NOWHERE;
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