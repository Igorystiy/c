#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void func_data_free(void* node_data);

char *int_to_char(int n) {
    char* c;
    c = (char *)malloc(10 * sizeof(char)); 
    int v = 0; //количество цифр в числе n
    //разбиваем на отдельные символы число n
    while (n > 9)
    {
        c[v++] = (n % 10) + '0';
        n = n / 10;
    }
    c[v++] = n + '0';
    c[v] = '\0';
    char t;
    //инвертируем массив символов
    for (int i = 0; i < v / 2; i++)
    {
        t = c[i];
        c[i] = c[v - 1 - i];
        c[v - 1 - i] = t;
    }
    v = 0;

    return (c);
}

int main() {
    printf("main->start->func_data_free addr=%lu\n", (size_t)&func_data_free);

    ts_list *s_list = list_create(&func_data_free, sizeof(char));

    char *ch = "test_str_";
    //s_list->add_node(s_list, ch, strlen(ch));
    //if (s_list->get_node(s_list, 10)) printf("main->get = OK\n");
    //else printf("main->get = ERR!!!\n");
    for (int i = 0; i < 101; i++) {
        //printf("main->add_node->for(%d)\n", i);
        //char *tmp = (char*)calloc(strlen(ch) + sizeof(char), sizeof(char));
        //memcpy(tmp, ch, strlen(ch));
        //tmp[strlen(ch)-1] = i + 50;
        //tmp[strlen(ch)] = '\0';
        //s_list->add_node(s_list, tmp, strlen(tmp) + sizeof(char));
        char *num = int_to_char(i);
        char *tmp = (char*)calloc(strlen(ch) + sizeof(char), sizeof(char));
        memcpy(tmp, ch, strlen(ch));
        memcpy(tmp + strlen(ch), num, strlen(num));

        s_list->add_node(s_list, tmp, strlen(tmp) + sizeof(char));

        free(tmp);
        free(num);
        //add_node(s_list, ch, strlen(ch) + sizeof(char));

        //free(tmp);
    }
    s_list->list_free(s_list);

    return (0);
}

void func_data_free(void* node_data) {
    //printf("main->free->%s\n", (char*)node_data);
    free(node_data);
}