#include "ush.h"

static t_variables *create_node(void *name, void *value) {
    t_variables *node =  (t_variables *)malloc(sizeof(t_variables));

    node->name = strdup(name);
    if(!value)
        node->value = strdup("");
    else
        node->value = strdup(value);
    node->next = NULL;
    return node;
}

void mx_push_variable(t_variables **list, void *name, void *value) {
    t_variables *tmp;
    t_variables *p;

    if (!list)
        return;
    tmp = create_node(name, value);  // Create new
    if (!tmp)
        return;
    p = *list;
    if (*list == NULL) {  // Find Null-node
        *list = tmp;
        return;
    }
    else {
        while (p->next != NULL)  // Find Null-node
            p = p->next;
        p->next = tmp;
    }
}
