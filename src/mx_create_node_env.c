#include "ush.h"

t_kv *mx_push_kv(char *env) { 
    t_kv *p = malloc(sizeof(t_kv));

    p->key = strndup(env, mx_get_char_index(env, '='));
    p->val = strndup(env + mx_get_char_index(env, '=') + 1,
                           strlen(env) - mx_get_char_index(env, '='));
    p->next = NULL;
    return p;
}

void mx_pushb_kv(t_kv **ptr, char *env) {
    t_kv *node = NULL;
    t_kv *tmp = NULL;

    if (!*ptr)
        return;
    node = mx_push_kv(env);
    tmp = *ptr;
    if (!*ptr) {
        *ptr = node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    return;
}
t_kv *mx_create_kv(char **environ) {
    t_kv *en = mx_push_kv(environ[0]);

    for (int i = 1; environ[i]; i++)
        mx_pushb_kv(&en, environ[i]);
    return en;
}
