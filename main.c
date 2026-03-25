#define PDC_WIDE
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "data_structure/data_structure.h"
#include "type/type_info.h"

int main() {
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) {
        clear();
        addwstr(L"Выберите тип текста:\n");
        addwstr(L"1) Латиница (char)\n");
        addwstr(L"2) Русский (wchar_t)\n");
        addwstr(L"3) HTML-кодированный\n");
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
        if (type == 0) continue;

        clear();
        addwstr(L"Введите текст (строку):\n");
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

        vector_dict *dict = NULL;
        if (type == 1) {
            dict = Create(txt, get_char_type());
        } else if (type == 2) {
            dict = Create(wtext, get_wchar_type());
        } else if (type == 3) {
            dict = Create(txt, get_html_type());
        }

        while (1) {
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
            addwstr(L"Введите номер вхождения (n):\n");
            refresh();
            echo();
            char nstr[10] = {0};
            getnstr(nstr, 9);
            noecho();
            int n = atoi(nstr);
 
            int pos = -1;
            if (type == 1) {
                pos = find(target, dict, n, get_char_type());
            } else if (type == 2) {
                pos = find(wword, dict, n, get_wchar_type());
            } else if (type == 3) {
                pos = find(target, dict, n, get_html_type());
            }

            clear();
            if (pos >= 0) {
                addwstr(L"Слово найдено по индексу: ");
                wchar_t idx[20];
                swprintf(idx, sizeof(idx)/sizeof(*idx), L"%d", pos);
                addwstr(idx);
                addwstr(L"\n");
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
