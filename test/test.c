#include "test.h"
#include <assert.h>
#include <stdio.h>
#include <wchar.h>

void print_sep() {
    printf(" ALL_OK\n\n");
}

void test_char_basic() {
    printf("test_char_basic:");

    vector_dict* d = Create("i am kostia", get_char_type());

    assert(find("i", d, 1, get_char_type()) == 0);
    assert(find("am", d, 1, get_char_type()) == 2);
    assert(find("kostia", d, 1, get_char_type()) == 5);

    free_data_struct(d);
    print_sep();
}

void test_char_repeated_words() {
    printf("test_char_repeated_words:");

    vector_dict* d = Create("one two one two one", get_char_type());

    assert(find("one", d, 1, get_char_type()) == 0);
    assert(find("one", d, 2, get_char_type()) == 8);
    assert(find("one", d, 3, get_char_type()) == 16);

    assert(find("two", d, 1, get_char_type()) == 4);
    assert(find("two", d, 2, get_char_type()) == 12);

    free_data_struct(d);
    print_sep();
}

void test_char_many_spaces() {
    printf("test_char_many_spaces:");

    vector_dict* d = Create("  alpha   beta    gamma ", get_char_type());

    assert(find("alpha", d, 1, get_char_type()) == 2);
    assert(find("beta", d, 1, get_char_type()) == 10);
    assert(find("gamma", d, 1, get_char_type()) == 18);

    free_data_struct(d);
    print_sep();
}

void test_char_not_found() {
    printf("test_char_not_found:");

    vector_dict* d = Create("a b c d", get_char_type());

    assert(find("x", d, 1, get_char_type()) == -1);
    assert(find("aa", d, 1, get_char_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_char_invalid_n() {
    printf("test_char_invalid_n:");

    vector_dict* d = Create("a a a", get_char_type());

    assert(find("a", d, 0, get_char_type()) == -1);
    assert(find("a", d, -1, get_char_type()) == -1);
    assert(find("a", d, 100, get_char_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_char_empty_and_only_spaces() {
    printf("test_char_empty_and_only_spaces:");

    vector_dict* d1 = Create("", get_char_type());
    assert(find("", d1, 1, get_char_type()) == -1);
    free_data_struct(d1);

    vector_dict* d2 = Create("     ", get_char_type());
    assert(find("", d2, 1, get_char_type()) == -1);
    free_data_struct(d2);

    print_sep();
}

void test_wchar_basic() {
    printf("test_wchar_basic:");

    vector_dict* d = Create(L"я и костя", get_wchar_type());

    assert(find(L"я", d, 1, get_wchar_type()) == 0);
    assert(find(L"и", d, 1, get_wchar_type()) == 2);
    assert(find(L"костя", d, 1, get_wchar_type()) == 4);

    free_data_struct(d);
    print_sep();
}

void test_wchar_repeated_words() {
    printf("test_wchar_repeated_words:");

    vector_dict* d = Create(L"привет саня как дела саня", get_wchar_type());

    assert(find(L"привет", d, 1, get_wchar_type()) == 0);
    assert(find(L"саня", d, 1, get_wchar_type()) == 7);
    assert(find(L"саня", d, 2, get_wchar_type()) == 21);
    assert(find(L"дела", d, 1, get_wchar_type()) == 16);

    free_data_struct(d);
    print_sep();
}

void test_wchar_many_spaces() {
    printf("test_wchar_many_spaces:");

    vector_dict* d = Create(L"\tпривет   мир\nкак\tдела", get_wchar_type());

    assert(find(L"привет", d, 1, get_wchar_type()) == 1);
    assert(find(L"мир", d, 1, get_wchar_type()) == 10);
    assert(find(L"как", d, 1, get_wchar_type()) == 14);
    assert(find(L"дела", d, 1, get_wchar_type()) == 18);

    free_data_struct(d);
    print_sep();
}

void test_wchar_not_found() {
    printf("test_wchar_not_found:");

    vector_dict* d = Create(L"один два три", get_wchar_type());

    assert(find(L"четыре", d, 1, get_wchar_type()) == -1);
    assert(find(L"од", d, 1, get_wchar_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_wchar_invalid_n() {
    printf("test_wchar_invalid_n:");

    vector_dict* d = Create(L"кот кот кот", get_wchar_type());

    assert(find(L"кот", d, 0, get_wchar_type()) == -1);
    assert(find(L"кот", d, -5, get_wchar_type()) == -1);
    assert(find(L"кот", d, 10, get_wchar_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_html_basic() {
    printf("test_html_basic:");

    vector_dict* d = Create("Hello&nbsp;world test", get_html_type());

    assert(find("Hello&nbsp;world", d, 1, get_html_type()) == 0);
    assert(find("test", d, 1, get_html_type()) == 12);
    assert(find("&nbsp;", d, 1, get_html_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_html_repeated_words() {
    printf("test_html_repeated_words:");

    vector_dict* d = Create("A&nbsp;B A&nbsp;B X", get_html_type());

    assert(find("A&nbsp;B", d, 1, get_html_type()) == 0);
    assert(find("A&nbsp;B", d, 2, get_html_type()) == 4);
    assert(find("X", d, 1, get_html_type()) == 8);

    free_data_struct(d);
    print_sep();
}

void test_html_not_found() {
    printf("test_html_not_found:");
    vector_dict* d = Create("one two three & & & && &&&&;;; ;; ;; ;;;;", get_html_type());

    assert(find("four", d, 1, get_html_type()) == -1);
    assert(find("&copy;", d, 1, get_html_type()) == -1);
    assert(find("&&&&", d, 1, get_html_type()) == -1);
    assert(find("&&;;", d, 1, get_html_type()) == -1);
    assert(find("&;", d, 1, get_html_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_html_invalid_n() {
    printf("test_html_invalid_n:");

    vector_dict* d = Create("a a a", get_html_type());
    assert(find("a", d, 0, get_html_type()) == -1);
    assert(find("a", d, -1, get_html_type()) == -1);
    assert(find("a", d, 100, get_html_type()) == -1);

    free_data_struct(d);
    print_sep();
}

void test_html_empty_and_spaces() {
    printf("test_html_empty_and_spaces:");

    vector_dict* d1 = Create("", get_html_type());
    assert(find("", d1, 1, get_html_type()) == -1);
    free_data_struct(d1);

    vector_dict* d2 = Create("     ", get_html_type());
    assert(find("", d2, 1, get_html_type()) == -1);
    free_data_struct(d2);

    print_sep();
}

void test_decode_html() {
    printf("test_decode_html:");
    char* decoded = decode_html_string("A&nbsp;B&lt;C&gt;");
    assert(strcmp(decoded, "A B<C>") == 0);
    free(decoded);
    char* decoded1 = decode_html_string("&euro;&pound;&deg;");
    assert(strcmp(decoded1, "€£°") == 0);
    free(decoded1);
    print_sep();
}


void all_test_all() {
    test_char_basic();
    test_char_repeated_words();
    test_char_many_spaces();
    test_char_not_found();
    test_char_invalid_n();
    test_char_empty_and_only_spaces();
    test_wchar_basic();
    test_wchar_repeated_words();
    test_wchar_many_spaces();
    test_wchar_not_found();
    test_wchar_invalid_n();
    test_html_basic();
    test_html_repeated_words();
    test_html_not_found();
    test_html_invalid_n();
    test_html_empty_and_spaces();
    test_decode_html();
    printf("ALL TESTS PASSED\n");
}


int main() {
    //тесты
    all_test_all();
    return 0;
}