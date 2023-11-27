#include "list.h"


ts_list
list_create(void *free_fn, size_t data_size) {
    return (ts_list){
        .data_size = data_size,
        .node_cnt = 0,
        .head_node = NULL,
        .free_fn = free_fn,
    };
}

bool
add_node(ts_list *list, void *data, size_t data_size) {
    if (list == NULL) {
        return false;
    }

    ts_node *new_node = malloc(sizeof(ts_node));

    if (new_node == NULL) {
        return false;
    }

    void *new_data = malloc(data_size);

    if (new_data == NULL) {
        return false;
    }

    memcpy(new_data, data, data_size);
    new_node->data = new_data;
    new_node->next_node = NULL;
    list->node_cnt++;

    if (list->head_node != NULL) {
        ts_node *last_node = get_last_node(list);
        last_node->next_node = new_node;
    } else {
        list->head_node = new_node;
    }

    return true;
}

ts_node *
get_last_node(ts_list *list) {

    ts_node *result = list->head_node;
    if (result != NULL) {
        ts_node *tmp = result;
        do {
            if (tmp != NULL) {
                result = tmp;
                tmp = tmp->next_node;
            }
        } while (tmp != NULL);
    }

    return (result);
}

ts_node *
get_node(ts_list *s_list, size_t pos) {
    ts_node *result = NULL;
    if (s_list) {
        if (pos < s_list->node_cnt) {
            result = s_list->head_node;
            bool f_stop = false;
            for (size_t cnt = 0; cnt < s_list->node_cnt && !f_stop;
                 cnt++) {
                if (cnt == pos) {
                    f_stop = true;
                } else {
                    result = result->next_node;
                    if (result == NULL)
                        f_stop = true;
                }
            }
        }
    }
    return (result);
}

void
list_free(ts_list *s_list) {
    if (s_list == NULL) {
        return;
    }

    for (size_t i = 0; i < s_list->node_cnt; i++) {
        s_list->free_fn(get_node(s_list, i)->data);
    }
}
