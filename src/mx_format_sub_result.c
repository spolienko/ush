#include "ush.h"

void mx_format_sub_result(char **str) {
    char *dst = NULL;
    char *tgt = NULL;
    int j = 0;

    if (str && *str) {
        tgt = mx_strtrim(*str);
        dst = mx_strnew(strlen(tgt));
        for (int i = 0; tgt[i] != '\0';) {
            if (!mx_isspace(tgt[i]))
                dst[j++] = tgt[i++];
            if (mx_isspace(tgt[i])) {
                dst[j++] = ' ';
                while(mx_isspace(tgt[i]))
                    i++;
            }
        }
        mx_strdel(&tgt);
        mx_strdel(str);
        *str = dst;
    }
}
