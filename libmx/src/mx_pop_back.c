#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list *p = NULL;

    if (!head || !(*head))
        return;
    if ((*head)->next == NULL) {
        (*head)->data = NULL;
        free(*head);
        *head = NULL;
        return;
    }
    else {
        p = *head;
        while (p->next->next != NULL)
            p = p->next;
        p->next->data = NULL;
        free(p->next);
        p->next = NULL;
    }
}
