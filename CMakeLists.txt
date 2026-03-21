cmake_minimum_required(VERSION 3.10)
project(TextSearch C)

set(CMAKE_C_STANDARD 99)

if(NOT MSVC)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

add_executable(text_search 
    data_structure.c
    main.c
    data_structure.h
    typeinfo.h
    Error.h
    test.h
)