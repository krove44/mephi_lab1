#pragma once

//первый тип это поиск по индексу в строке
//второй тип это поиск по счету в какой строке элемент и его индекс в этой строке

typedef enum 
{
    first_type = 0,
    second_type
}typeinfo;

typeinfo get_first_type();
typeinfo get_second_type();
