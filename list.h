#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ts_list ts_list;

typedef struct s_node {
    void *data;
    struct s_node *next_node;
} ts_node;

typedef struct ts_service {
} ts_service;

struct ts_list {
    size_t data_size;
    size_t node_cnt;
    ts_node *head_node;
    void (*free_fn)(void *);
};

ts_list list_create(void *free_fn, size_t data_size);
bool add_node(ts_list *s_list, void *data, size_t data_size);
ts_node *get_last_node(ts_list *s_service);
ts_node *get_head_node(ts_list *s_list);
ts_node *get_node(ts_list *s_list, size_t pos);
void list_free(ts_list *s_list);

#endif
