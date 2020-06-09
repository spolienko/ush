#include "ush.h"

static int count_par(char *line) {
    int count = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i+1] && line[i] == '$' && line[i+1] == '{') {
            if (i > 0 && line[i-1] == '\\')
                continue;
            i += 2;
            if (line[i] == '}')
                return -1;
            for(; line[i] && line[i] != '}'; i++)
                if (line[i] == '`' || line[i] == ' ' || (line[i+1] && line[i] == '$' && (line[i+1] == '{' || line[i+1] == '(')))
                    return -1;
            if (line[i] && line[i] == '}')
                count++;
            else
                return -1;
        }
    }
    return count;
}

static char *arr_from_j_to_i(char *line, int *beg, int end) {
    int len = end - *beg;
    char *res = mx_strnew(len);
    char *result = NULL;

    for (int i = 0; i < len;) {
        res[i++] = line[(*beg)++];
    }
    (*beg) = 0;
    result = mx_strtrim(res);
    mx_strdel(&res);
    if (mx_strlen(result) > 0)
        return result;
    return NULL;
}

static int count_len_par(char *line) {
    int len = mx_strlen(line);
    int j = 0;
    char *param = NULL;

    for (int i = 0; line[i]; i++) {
        if (line[i+1] && line[i] == '$' && line[i+1] == '{') {
            if (i > 0 && line[i-1] == '\\')
                continue;
            j = i + 2;
            while (line[i] && line[i] != '}')
                i++;
            if (line[i] && line[i] == '}') {
                len -= i - j - 3;
                param = arr_from_j_to_i(line, &j, i);
                if (param && getenv(param)) {
                    len += mx_strlen(getenv(param));
                    mx_strdel(&param);
                }
            }
        }
    }
    return len;
}

static char *expn_par(char *line, int len) {
    char *res = mx_strnew(len);
    char *param = NULL;
    int j = 0;
    int r = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i+1] && line[i] == '$' && line[i+1] == '{') {
            if (i > 0 && line[i-1] == '\\') {
                res[r++] = '$';
                continue;
            }
            j = i + 2;
            while (line[i] && line[i] != '}')
                i++;
            if (line[i] && line[i] == '}') {
                param = arr_from_j_to_i(line, &j, i);
                if (param && getenv(param)) {
                    mx_exp_join(&res, strdup(getenv(param)), &r);
                    mx_strdel(&param);
                }
            }
        }
        else if (line[i]) {
            res[r++] = line[i];
            res[r] = '\0';
        }
    }
    return res;
} // 20+ lines 5 variables;

char *mx_exp_param(char **line) {
    char *res = NULL;
    int len = 0;
    int count = count_par(*line);

    if (count > 0) {
        len = count_len_par(*line);
        res = expn_par(*line, len);
        mx_strdel(line);
    } else if (count == -1) {
        mx_strdel(line);
        return NULL;
    }
    else
        res = *line;
    return res;
}
