#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *new = mx_create_node(data);
    t_list *last = *list;

    new->data = data;
    new->next = NULL;
    if (*list == NULL) {
        *list = new;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
    return;
}
