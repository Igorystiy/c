#include "list.h"

ts_list *list_create(void *callback_free_data, size_t data_size) {
printf("list->create->callback addr=%lu\n", (size_t)callback_free_data);
printf("list->create->size ts_list=%lu, size ts_service=%lu, size ts_node=%lu, size *void=%lu, size size_t=%lu\n", 
    sizeof(ts_list), sizeof(ts_service), sizeof(ts_node), sizeof(void*), 
    sizeof(size_t));
    
    ts_list *result = (ts_list*)malloc(sizeof(ts_list)) + DIFF + sizeof(ts_service) + DIFF;
    //ts_list *result = (ts_list*)malloc(sizeof(ts_list));
    if (result) {
        result->add_node = &add_node;
        result->get_node = &get_node;
        result->get_nodes_cnt = &get_nodes_cnt;
        result->list_free = &list_free;

        //ts_service *s_service = (ts_service*)malloc(sizeof(ts_service));
        //void *list = (void*)result;
        ts_service *s_service = (ts_service*)((void*)result + sizeof(ts_list) + DIFF);//+ DIFF + sizeof(ts_list));
        s_service->data_size = data_size;
        s_service->func_data_free = callback_free_data;
        s_service->node_cnt = 0;
        s_service->head_node = NULL;

        result->service = s_service;

        printf("list->create->list addr=%lu, service addr=%lu\n", (size_t)result, (size_t)s_service);
        printf("list->create->list addr=%lu, service addr=%lu\n", (size_t)result, (size_t)(result->service));
    }

    return (result);
}

bool add_node(ts_list *s_list, void *data, size_t data_size) {
    bool result = true;

    //printf("list->add_node->s_list(0x%p)...\n", s_list);
    if (s_list) {
        //printf("list->add_node(0x%p), size=%lu, data=%s\n", data, data_size, (char*)data);        
        //if (s_service->head_node) {
            ts_node *new_node = (ts_node*)malloc(sizeof(ts_node));
            if (new_node) {
                void *new_data = calloc(1, data_size);
                if (new_data) {
                    memcpy(new_data, data, data_size);
                    new_node->data = new_data;
                    new_node->next_node = NULL;
                    //ts_service *s_service = (ts_service*)(s_list + DIFF + sizeof(ts_list));
                    ts_service *s_service = s_list->service;
                    if (s_service->head_node) {
                        printf("list->add_node->new_node('%s')\n", (char*)new_node->data);
                        get_last_node(s_service)->next_node = new_node;
                    }
                    else {
                        //printf("list->add_node->new_node to HEAD!\n");
                        s_service->head_node = new_node;
                    }
                    s_service->node_cnt++;
                } else result = false;
            } else result = false;
        //}
    } else result = false;

//printf("list->add_node->s_list(0x%p)=OK\n", s_list);

    return (result);
}

ts_node *get_last_node(ts_service *s_service) {
//printf("list->get_last_node->s_service(0x%p)...\n", s_service);

    ts_node *result = s_service->head_node;
    //bool f_stop = false;
    if (result != NULL) {
        ts_node *tmp = result;
        //int cnt = 0;
        do {
            //printf("list(%u)->get_last_node(%s), h_node('%s')-> do...\n", 
                //s_service->node_cnt, (char*)s_service->head_node->data, (char*)result->data);
            if (tmp != NULL) {
                result = tmp; 
                tmp = tmp->next_node;
            }
            //if (tmp->next_node == NULL) f_stop = true;
            //else {result = tmp; tmp = tmp->next_node;}
        //} while (!f_stop);
        //if (cnt++ > 100) break;
        }while (tmp != NULL);
    }

    //printf("list->get_last_node->s_service(0x%p)=OK\n", s_service);

    return (result);
}

ts_node *get_head_node(ts_list *s_list) {
//printf("list->get_head_node->s_list(0x%p)...\n", s_list);

    ts_node *result = NULL;

   if (s_list != NULL) {
        //ts_service *s_service = (ts_service*)(s_list + DIFF + sizeof(ts_list));
        ts_service *s_service = s_list->service;
        result = s_service->head_node;
   }
//printf("list->get_head_node->s_list(0x%p)=OK\n", s_list);
    return (result);
}

ts_node *get_node(ts_list *s_list, size_t pos) {
    ts_node *result = NULL;
//printf("list->get_node->s_list(0x%p)...\n", s_list);
    if (s_list) {
        if (pos < get_nodes_cnt(s_list)) {
            result = get_head_node(s_list);
            bool f_stop = false;
            for (size_t cnt = 0; cnt < get_nodes_cnt(s_list) && !f_stop; cnt++) {
                //printf("list->get_node->for(%u)\n", cnt);
                if (cnt == pos) {
                    //printf("list->get_node->cnt(%lu) = pos(%lu)\n", cnt, pos);
                    f_stop = true;
                }
                else {
                    //printf("list->get_node->cnt(%u) != pos(%u)\n", cnt, pos);
                    result = result->next_node;
                    if (result == NULL) f_stop = true;
                }
                }
            }
    }
//printf("list->get_node->s_list(0x%p)=OK\n", s_list);
  return (result);
}

size_t get_nodes_cnt(ts_list *s_list) {
    size_t result = 0;
//printf("list->get_node_cnt->s_list(0x%p)...\n", s_list);
    if (s_list != NULL) {
        //result = ((ts_service*)(s_list + DIFF + sizeof(ts_list)))->node_cnt;
        result = s_list->service->node_cnt;
    }
//printf("list->get_node_cnt->s_list(0x%p)=OK\n", s_list);
    return (result);
}

void list_free(ts_list *s_list) {
    if (s_list) {
        //printf("list->free(%u)->%p\n",get_nodes_cnt(s_list), s_list);
        for (size_t i = 0; i < get_nodes_cnt(s_list); i++) {
            //ts_service *s_service = (ts_service*)(s_list + DIFF + sizeof(ts_list));
            ts_service *s_service = s_list->service;
            //printf("list->free->for(%u)...\n", i);
            s_service->func_data_free(get_node(s_list, i)->data);
            //printf("list->free->for(%u)=OK\n", i);
        }
    free(s_list);
    }
}