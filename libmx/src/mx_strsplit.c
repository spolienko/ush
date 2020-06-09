#include "libmx.h"

static char** split_word(const char *s, char c, char ** arr);
static int mx_count_words_local(const char *str, char c);

char **mx_strsplit(const char *s, char c) {
    int count = mx_count_words_local(s, c);
    char** arr = (char**)malloc(sizeof(char*) * count + 1);

    if(!s)
        return NULL;
    if (count == 1) {
        arr[0] =  mx_strdup(s);
        arr[1] = NULL;
        return arr;
    }
    return split_word(s, c, arr);
}

static int mx_count_words_local(const char *str, char c) {
    int count = 0;
    int i = 0;

    if (str == NULL)
        return -1;
    while (str[i] != '\0') {
        while (str[i] == c && str[i] != '\0')
            i++;
        if (str[i] != c && str[i] != '\0')
            count++;
        while (str[i] != c && str[i] != '\0')
            i++;   
    }
    return count;
}

static char** split_word(const char *s, char c, char **arr) {
    int j = 0;
    int letters = 0;
    int word = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        while (s[i] != c && s[i] != '\0') {
             word = 1;
             letters++;
             i++;
        }
        if (word) {
            arr[j] = mx_strnew(letters);
            arr[j] = mx_strncpy(arr[j], s + i - letters, letters);
            word = 0;
            letters = 0;
            j++;
        }
    }
    arr[j] = NULL;
    return arr;
}
