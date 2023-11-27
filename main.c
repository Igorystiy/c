#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void func_data_free(void *node_data);

char *
int_to_char(int n) {
    char *c;
    c = (char *)malloc(10 * sizeof(char));
    int v = 0; // количество цифр в числе n
    // разбиваем на отдельные символы число n
    while (n > 9) {
        c[v++] = (n % 10) + '0';
        n = n / 10;
    }
    c[v++] = n + '0';
    c[v] = '\0';
    char t;
    // инвертируем массив символов
    for (int i = 0; i < v / 2; i++) {
        t = c[i];
        c[i] = c[v - 1 - i];
        c[v - 1 - i] = t;
    }
    v = 0;

    return (c);
}

int
main() {
    ts_list s_list = list_create(&free, sizeof(char));

    char ch[] = "test_str_";
    size_t ch_size = sizeof(ch);
    for (int i = 0; i < 101; i++) {
        char *num = int_to_char(i);
        size_t num_len = strlen(num);

        char *tmp = malloc(ch_size + num_len + 1);
        memcpy(tmp, ch, ch_size - 1);
        memcpy(tmp + ch_size - 1, num, num_len);
        *(num + ch_size - 1 + num_len + 1) = 0;

        add_node(&s_list, tmp, strlen(tmp) + sizeof(char));

        free(tmp);
        free(num);
    }
    list_free(&s_list);

    return (0);
}
