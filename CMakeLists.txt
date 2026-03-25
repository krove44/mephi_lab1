cmake_minimum_required(VERSION 3.10)
project(TextSearch C)

set(CMAKE_C_STANDARD 99)

if(NOT MSVC)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/type
    ${CMAKE_SOURCE_DIR}/data_structure
    ${CMAKE_SOURCE_DIR}/test
    ${CMAKE_SOURCE_DIR}/curser/include
)

link_directories(${CMAKE_SOURCE_DIR}/curser/lib)

add_executable(tests
    data_structure/data_structure.c
    type/char_type.c
    type/wchar_type.c
    type/html_type.c
    test/test.c
)

add_executable(ui_app
    main.c
    data_structure/data_structure.c
    type/char_type.c
    type/wchar_type.c
    type/html_type.c
)

target_compile_definitions(ui_app PRIVATE PDC_WIDE)
target_link_libraries(ui_app pdcurses)