#include "ui.h"
void start_interface() {
    char text_buf[1024];
    wchar_t w_text_buf[1024];
    
    char search_buf[256];
    wchar_t w_search_buf[256];

    int choice;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
    }
    
    printw("=== TEXT SEARCH SYSTEM ===\n\n");
    printw("Choose mode:\n");
    printw("1. Standard Char\n");
    printw("2. Wide Char (Unicode)\n");
    printw("3. HTML Encoding Mode (Smart Indices)\n");
    printw("\nYour choice: ");
    refresh();
    
    choice = getch();
    clear();

    vector_dict* sany = NULL;
    size_t pos = (size_t)-1;
    type_info* current_type = NULL;

    if (choice == '2') {
        current_type = get_wchar_type();
        printw("Enter the main text (WIDE):\n> ");
        refresh();
        echo();

        wgetn_wstr(stdscr, (wint_t*)w_text_buf, 1023); 
        
        noecho();
        sany = Create(w_text_buf, current_type);

        printw("\n\nEnter word to find: ");
        refresh();
        echo();
        wgetn_wstr(stdscr, (wint_t*)w_search_buf, 255);
        noecho();

        pos = find(w_search_buf, sany, 1, current_type);
    }
    else if (choice == '3') {
        current_type = get_html_type();
        printw("Enter HTML text (e.g. A&copy;B):\n> ");
        refresh();
        echo();
        getnstr(text_buf, sizeof(text_buf) - 1);
        noecho();

        sany = Create(text_buf, current_type);

        printw("\n\nEnter word or symbol (e.g. &copy; or ©): ");
        refresh();
        echo();
        getnstr(search_buf, sizeof(search_buf) - 1);
        noecho();

        pos = find(search_buf, sany, 1, current_type);
    }
    else {
        current_type = get_char_type();
        printw("Enter the main text:\n> ");
        refresh();
        echo();
        getnstr(text_buf, sizeof(text_buf) - 1);
        noecho();

        sany = Create(text_buf, current_type);

        printw("\n\nEnter word to find: ");
        refresh();
        echo();
        getnstr(search_buf, sizeof(search_buf) - 1);
        noecho();

        pos = find(search_buf, sany, 1, current_type);
    }

    move(14, 0); 
    if (pos != (size_t)-1) {
        if (has_colors()) attron(COLOR_PAIR(1));
        attron(A_BOLD);
        printw("SUCCESS: Word found at logical position %zu\n", pos);
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
    } else {
        printw("RESULT: Not found.\n");
    }

    printw("\nPress any key to exit...");
    refresh();
    getch();

    if (sany) free_data_struct(sany);
    endwin();
}