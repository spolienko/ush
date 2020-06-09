#include "ush.h"

static void del_backslashes(char **line) {
    int len = strlen(*line);
    char *res = mx_strnew(len);
    int r = 0;


    for(int i = 0; i < len && (*line)[i]; i++) {
        if ((*line)[i] == '\\')
            i++;
        res[r++] = (*line)[i];
    }
    mx_strdel(line);
    *line = res;
}

static char *sub_line(char *line, int *i, t_shell *shell) {
    int len = 0;
    int start = *i;
    char *res = NULL;
    int flg_qte_sub = 0;
    int notquoted = 0;
    int notdquoted = 0;
    int count = 1;

    if (line[*i] == '$') {
        *i+=2, start += 2;
        len--;
        for(count = 1; count != 0 && line[*i]; (*i)++) {
            if ((line[*i] == '$' && line[*i+1] == '(') && line[*i-1] != '\\')
                count++;
            if (line[*i] == '"')
                notdquoted = (notdquoted == 0) ? 1 : 0;
            if (line[*i] == '\'')
                notquoted = (notquoted == 0) ? 1 : 0;
            if (line[*i] == ')' && line[*i-1] != '\\' && notdquoted == 0 && notquoted == 0) {
                count--;
            }
            if (line[*i] == '`' && flg_qte_sub == 0 && line[*i-1] != '\\') {
                flg_qte_sub = 1;
                count++;
            }
            if (line[*i] == '`' && flg_qte_sub == 1 && line[*i-1] != '\\') {
                flg_qte_sub = 0;
                count--;
            }
            len++;
        }
        if (count != 0)
            mx_printerr("error parse in substitution");
        res = len > 0 ? mx_strndup(&line[start], len) : NULL;
    }
    if (line[*i] == '`') {
        (*i)++, start++;
        len--;

        for(count = 1; count != 0 && line[*i]; (*i)++) {
            if ((line[*i] == '$' && line[*i+1] == '(') && line[*i-1] != '\\')
                count++;
            if (line[*i] == '"')
                notdquoted = (notdquoted == 0) ? 1 : 0;
            if (line[*i] == '\'')
                notquoted = (notquoted == 0) ? 1 : 0;
            if (line[*i] == ')' && line[*i-1] != '\\' && notquoted == 0 && notdquoted == 0) {
                count--;
            }
            if (line[*i] == '`' && line[*i-1] != '\\') {
                count--;
            }
            len++;
        }
        if (count != 0)
            mx_printerr("error parse in substitution");
        res = len > 0 ? mx_strndup(&line[start], len) : NULL;
        if (res)
            del_backslashes(&res);
    }
    if (count != 0) {
        mx_strdel(&res);
        shell->status = 901;
    }
    else
        shell->status = 902;
    return res;
}

static void get_sub_index(char *subst, t_sub *sub_num) {
    int len = strlen(subst);
    int i = sub_num->index;

    while(i < len && subst[i]) {
        if (subst[i] == '"')
            sub_num->d_quote = sub_num->d_quote == 0 ? 1 : 0;
        if (subst[i] == '\'')
            sub_num->quote = sub_num->quote == 0 ? 1 : 0;
        if ((subst[i] == '$' && subst[i+1] == '(') || subst[i] == '`') {
            if (i > 0 && subst[i-1] == '\\') {
                
                i++;
                continue;
            }
            break;
        }
        i++;
    }
    sub_num->index = subst[i] && i < len ? i : -1;
}

static void sub_desc_init(t_fd *desc) {
    desc->saved_stdin = dup(0);
    desc->saved_stdout = dup(1);
    desc->output_fds = open("./output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    desc->input_fds = open("./output.txt", O_RDONLY);
}

static void sub_num_init(t_sub *sub_num) {
    sub_num->index = 0;
    sub_num->quote = 0;
    sub_num->d_quote = 0;
}

static void sub_menu(char *substitution, char **line, t_shell *shell) {
    t_sub *sub_num = (t_sub *)malloc(sizeof(t_sub));
    t_fd *desc = (t_fd *)malloc(sizeof(t_fd));
    t_li *forest = NULL;
    char *subling = NULL;

    sub_num_init(sub_num);
    get_sub_index(substitution, sub_num);
    while (sub_num->index != -1) {
        subling = sub_line(substitution, &sub_num->index, shell);
        if (!subling) {
            mx_strdel(line);
            return;
        }
        sub_menu(subling, &substitution, shell);
        mx_strdel(&subling);
        get_sub_index(substitution, sub_num);
    }
    sub_desc_init(desc);
    dup2(desc->output_fds, STDOUT_FILENO);
    forest = mx_create_forest(substitution);
    mx_launch_cmd(forest, shell);
    dup2(desc->saved_stdout, STDOUT_FILENO);
    close(desc->output_fds);
    close(desc->saved_stdout);


    dup2(desc->input_fds, STDIN_FILENO);
    char *sub_result = NULL;
    char *res = NULL;
    int r = 0;
    int len_res = strlen(*line);

    sub_result = mx_str_from_stdin();
    if (sub_result) {
        if (sub_num->d_quote == 0 && sub_num->quote == 0)
            mx_format_sub_result(&sub_result);

        len_res += strlen(sub_result);
        res = mx_strnew(len_res);
    }
    res = mx_strnew(len_res);
    remove("./output.txt");

    for(int i = 0; (*line)[i]; i++) {
        if ((*line)[i] == '`' || ((*line)[i] == '$' && (*line)[i+1] == '('))
            if (i > 0 && (*line)[i-1] != '\\') {
                for(int beg = 0; sub_result && sub_result[beg]; beg++)
                    res[r++] = sub_result[beg];
                subling = sub_line(*line, &i, shell);
                mx_strdel(&subling);
            }
        res[r++] = (*line)[i];
    }
    *line = res;
    dup2(desc->saved_stdin, STDIN_FILENO);
    close(desc->input_fds);
    close(desc->saved_stdin);
}

char *mx_substitutions(char *line, t_shell *shell) {
    t_sub *sub_num = (t_sub *)malloc(sizeof(t_sub));
    char *substitution = NULL;

    sub_num->index = 0;
    sub_num->quote = 0;
    sub_num->d_quote = 0;
    get_sub_index(line, sub_num);
    while (sub_num->index != -1) {
        substitution = sub_line(line, &sub_num->index, shell);
        if (shell->status == 901)
            mx_strdel(&line);
        else {
            sub_menu(substitution, &line, shell);
            if (substitution)
                mx_strdel(&substitution);
        }
        if (!line)
            return NULL;
        get_sub_index(line, sub_num);
    }
    return line;
}
