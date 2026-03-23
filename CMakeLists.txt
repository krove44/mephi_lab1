cmake_minimum_required(VERSION 3.10)
project(TextSearch C)

set(CMAKE_C_STANDARD 99)

if(NOT MSVC)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/curser/include
    ${CMAKE_SOURCE_DIR}/type
    ${CMAKE_SOURCE_DIR}/data_structure
    ${CMAKE_SOURCE_DIR}/test
    ${CMAKE_SOURCE_DIR}/ui
)

link_directories(${CMAKE_SOURCE_DIR}/curser/lib)

add_executable(text_search 
    data_structure/data_structure.c
    main.c
    ui/ui.c
    type/char_type.c
    type/wchar_type.c
    type/html_type.c
    test/test.c
)

target_link_libraries(text_search pdcurses)