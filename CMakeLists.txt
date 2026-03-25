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
    ${CMAKE_SOURCE_DIR}/ui
    ${CMAKE_SOURCE_DIR}/curser/include
)

link_directories(${CMAKE_SOURCE_DIR}/curser/lib)

#библиотеки
add_library(core
    data_structure/data_structure.c
    type/char_type.c
    type/wchar_type.c
    type/html_type.c
)

# curser
add_executable(ui_app
    main.c
    ui/ui.c
)

target_link_libraries(ui_app core pdcurses)
target_compile_definitions(ui_app PRIVATE PDC_WIDE)

# тесты
add_executable(tests
    test/test.c
)

target_link_libraries(tests core)
