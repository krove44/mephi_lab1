#ifndef PDC_WIDE
#define PDC_WIDE
#endif

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <curses.h>
#include "data_structure/data_structure.h"
#include "type/type_info.h"

static type_info* get_selected_type(int type) {
    if (type == 1) return get_char_type();
    if (type == 2) return get_wchar_type();
    return get_html_type();
}

static void show_dictionary(vector_dict *dict, type_info *type) {
    def_prog_mode();
    endwin();

    print_d(dict, type);
    wprintf(L"\nНажмите Enter, чтобы вернуться в меню...");
    fflush(stdout);

    int ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    reset_prog_mode();
    refresh();
}

int main() {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) {
        clear();
        addwstr(L"Выберите тип текста:\n");
        addwstr(L"1) Обычный текст (char)\n");
        addwstr(L"2) Широкие символы (wchar_t)\n");
        addwstr(L"3) HTML\n");
        addwstr(L"(Нажмите 'q' для выхода)\n");
        refresh();

        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }

        int type = 0;
        if (ch == '1') type = 1;
        if (ch == '2') type = 2;
        if (ch == '3') type = 3;
        if (type == 0) {
            continue;
        }

        clear();
        addwstr(L"Введите текст:\n");
        refresh();
        echo();

        wint_t wbuf[1024] = {0};
        getn_wstr(wbuf, 1023);
        noecho();

        wchar_t *wtext = (wchar_t*)wbuf;
        char txt[1024] = {0};
        if (type == 1 || type == 3) {
            wcstombs(txt, wtext, sizeof(txt));
        }

        type_info *current_type = get_selected_type(type);
        vector_dict *dict = NULL;
        if (type == 1) {
            dict = Create(txt, current_type);
        } else if (type == 2) {
            dict = Create(wtext, current_type);
        } else {
            dict = Create(txt, current_type);
        }

        while (1) {
            clear();
            addwstr(L"Выберите действие:\n");
            addwstr(L"1) Найти слово\n");
            addwstr(L"2) Вывести все слова с позициями\n");
            addwstr(L"b) Назад\n");
            refresh();

            int action = getch();
            if (action == 'b' || action == 'B') {
                break;
            }
            if (action == '2') {
                show_dictionary(dict, current_type);
                continue;
            }
            if (action != '1') {
                continue;
            }

            clear();
            addwstr(L"Введите слово для поиска (или 'b' для возврата):\n");
            refresh();
            echo();

            wint_t wtarget[256] = {0};
            getn_wstr(wtarget, 255);
            noecho();

            wchar_t *wword = (wchar_t*)wtarget;
            if (wword[0] == L'b' && wword[1] == L'\0') {
                break;
            }

            char target[256] = {0};
            if (type == 1 || type == 3) {
                wcstombs(target, wword, sizeof(target));
            }

            clear();
            addwstr(L"Введите номер вхождения n:\n");
            refresh();
            echo();

            char nstr[10] = {0};
            getnstr(nstr, 9);
            noecho();

            int n = atoi(nstr);
            int pos = -1;
            if (type == 1) {
                pos = find(target, dict, n, current_type);
            } else if (type == 2) {
                pos = find(wword, dict, n, current_type);
            } else {
                pos = find(target, dict, n, current_type);
            }

            clear();
            if (pos >= 0) {
                wchar_t result[128];
                swprintf(result, sizeof(result) / sizeof(*result),
                         L"Слово найдено на позиции: %d\n", pos);
                addwstr(result);
            } else {
                addwstr(L"Слово не найдено\n");
            }
            addwstr(L"Нажмите любую клавишу, чтобы продолжить...");
            getch();
        }

        free_data_struct(dict);
    }

    endwin();
    return 0;
}
