
#include "ush.h"

static char ** mx_strsplit_local(const char *s, char c) {
    if (!s)
        return NULL;
    int count_words = mx_count_words(s, c);
    char **arr_words = (char **)malloc((count_words + 1 ) * sizeof(char*));
    int len_w = 0;

    for (int j = 0; *s != '\0'; s++) {
        if (*s != c) {
            len_w++;
            if (*(s + 1) == '\0') {
                arr_words[j] = mx_strncpy(mx_strnew(len_w), (s - len_w + 1) ,len_w);
                break;
            }
        }
        else if (*s == c) {
            if (len_w == 0);
            else if (len_w != 0) {
                arr_words[j] = mx_strncpy(mx_strnew(len_w), (s - len_w) ,len_w);
                len_w =  0;
                j++;
            }
        }
    }
    arr_words[count_words] = NULL;
    return (arr_words) ? arr_words : NULL;
}

static char **get_arr(char *dir) {
    char **arr = NULL;
    int i = 0;

    arr = mx_strsplit_local(dir, '/');
    while (arr[i] != NULL) {
        if (strcmp(arr[i], ".") == 0) {
            free(arr[i]);
            arr[i] = mx_strnew(1);
        }
        if (strcmp(arr[i], "..") == 0) {
            free(arr[i]);
            arr[i] = mx_strnew(1);
            for (int j =i; j >= 0; j--) {
                if(strcmp(arr[j], "") != 0) {
                    free(arr[j]);
                    arr[j] = mx_strnew(1);
                    break ;
                }
            }
        }
        i++;
    }
    return arr;
}

static char *mx_directory_path(char **array) {
    int i = 0;
    char *directory_path = NULL;

    while (array[i] != NULL) {
        if (strcmp(array[i], "") != 0) {
            char *tmp = mx_strjoin(directory_path, "/");
            if (directory_path)
                free(directory_path);
            directory_path = mx_strjoin(tmp, array[i]);
            free(tmp);
        }
        i++;
    }
    if (!directory_path)
        directory_path = strdup("/");

    return directory_path;
}

char *mx_output_path(char *path, char *move_to) {
    char *current_diratory = strdup(path);
    char *directory = NULL;
    char **arr = NULL;

    if (move_to[0] == '/') {
        directory = strdup(move_to);
    }
    else {
        char *tmp = mx_strjoin(current_diratory, "/");
        free(directory);
        directory = mx_strjoin(tmp, move_to);
        free(tmp);
    }
    arr = get_arr(directory);
    free(directory);
    directory = mx_directory_path(arr);
    mx_del_strarr(&arr);
    free(current_diratory);
    return directory;
}
