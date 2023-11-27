#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DIFF 8


typedef struct ts_list ts_list;

// 16 b
typedef struct s_node {
    void *data;                         //8 b
    struct s_node *next_node;           //8 b
} ts_node;

// 24 b
typedef struct ts_service {
    void (*func_data_free)(void*);      // 8 b
    size_t data_size;                   // 8 b 
    size_t node_cnt;                    // 8 b
    ts_node *head_node;                 // 8 b
} ts_service;

// 40 b
struct ts_list {
    bool (*add_node)(ts_list*, void*, size_t);          // 8 b
    ts_node *(*get_node)(ts_list *s_list, size_t pos);  // 8 b
    size_t (*get_nodes_cnt)(ts_list *s_list);           // 8 b
    void (*list_free)(ts_list *s_list);                 // 8 b

    ts_service *service;                                // 8 b
 };


ts_list *list_create(void *callback_free_data, size_t data_size);
bool add_node(ts_list *s_list, void* data, size_t data_size);
ts_node *get_last_node(ts_service *s_service);
ts_node *get_head_node(ts_list *s_list);
ts_node *get_node(ts_list *s_list, size_t pos);
size_t get_nodes_cnt(ts_list *s_list);
void list_free(ts_list *s_list);

#endif