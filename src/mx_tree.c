#include "ush.h"

t_cmd *mx_create_cmd(char *cmd, int i) {
    t_cmd *tr = malloc(sizeof(t_cmd));
    char *temp = NULL;

    if (cmd) {
        temp = mx_strndup(cmd, i);
        tr->cmd = mx_trim_token(temp); // check escape space
        free(temp);
        temp = NULL;
    }
    else
        tr->cmd = NULL;
    tr->or = NULL;
    tr->and = NULL;
    return tr;
}

static char **create_arr_tree(char *tok) {
    int count = 1;
    int i = 0;
    int j = 0;
    char **tmp = NULL;
    int flag_quote = 0;
    int flag_dquote = 0;

    for (i = 0; tok[i]; i++) {
        if (tok[i] == '"' || tok[i] == '\'') {
            if (i > 0 && tok[i-1] == '\\')
                continue;
            if (tok[i] == '\'' && flag_dquote == 0)
                flag_quote = 1 ? flag_quote == 0 : 0;
            if (tok[i] == '"' && flag_quote == 0)
                flag_dquote = 1 ? flag_dquote == 0 : 0;
            continue;
        }
        if (flag_quote == 1 || flag_dquote == 1)
            continue;
        if (tok[i] == '&' && tok[i+1] == '&') {
            if (i > 1 && tok[i-1] == '\\')
                continue;
            count++;
        }
    }
    tmp = malloc((count + 1) * sizeof(char *));
    for (i = 0; tok[i]; i++) {
        if (tok[i] == '"' || tok[i] == '\'') {
            if (i > 0 && tok[i-1] == '\\')
                continue;
            if (tok[i] == '\'' && flag_dquote == 0)
                flag_quote = 1 ? flag_quote == 0 : 0;
            if (tok[i] == '"' && flag_quote == 0)
                flag_dquote = 1 ? flag_dquote == 0 : 0;
            continue;
        }
        if (flag_quote == 1 || flag_dquote == 1)
            continue;
        if (tok[i] == '&' && tok[i+1] == '&') {
            if (i > 1 && tok[i-1] == '\\')
                continue;
            tmp[j] = mx_strndup(tok, i);
            tok += i + 2;
            i = 0;
            j++;
        }
    }
    tmp[j] = mx_strndup(tok, i);
    tmp[j+1] = NULL;
    return tmp;
}

static void fillthat(char *tok, t_cmd **tr) {
    int j = 0;

    for (j = 0; tok[j]; j++) {
        if (tok[j] == '|' && tok[j+1] == '|') {
            if (j > 1 && tok[j-1] == '\\')
                continue;
            if ((*tr)->cmd == NULL)
                (*tr)->cmd = mx_strndup(tok, j);
            else {
                (*tr)->or = mx_create_cmd(tok, j);
                (*tr) = (*tr)->or;
            }
            tok += j + 2;
            j = 0;
        }
    }
    if ((*tr)->cmd == NULL)
        (*tr)->cmd = mx_strndup(tok, j);
    else {
        (*tr)->or = mx_create_cmd(tok, j);
        (*tr) = (*tr)->or;
    }
}

t_cmd *mx_treefill(char *tok) {
    t_cmd *tree = mx_create_cmd(NULL, 0);
    t_cmd *tr = tree;
    char **tmp = create_arr_tree(tok);
    int i = 0;

    for (i = 0; tmp[i]; i++) {
        tok = mx_trim_token(tmp[i]); // check for escape space
        fillthat(tok, &tr);
        if (tmp[i + 1]) {
            tr->and = mx_create_cmd(NULL, 0);
            tr = tr->and;
        }
    }
    return tree;
}

void mx_pushtree(t_li **forest, char *tokcoma) {
    t_li *new = malloc(sizeof(t_li));
    t_li *last = *forest;

    new->command = mx_treefill(tokcoma);
    new->next = NULL;
    if (*forest == NULL) {
        *forest = new;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new;
}
