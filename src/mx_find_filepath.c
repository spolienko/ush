#include "ush.h"

int mx_find_filepath(char **cmd_arr, char **filepath) {
    char *path = strdup(getenv("PATH"));
    char *token = NULL;
    DIR *dptr;
    struct dirent *ds;
    struct stat buf;
    
    if (lstat(cmd_arr[0], &buf) != -1) {
        if((buf.st_mode & S_IXUSR) == S_IXUSR)
            *filepath = mx_strdup(cmd_arr[0]);
            return 2;
    }
    if (path)
        token = strtok(path, ":");
    for (; token; token = strtok(NULL, ":")) {
        if ((dptr = opendir(token)) != NULL) {
            for (; (ds = readdir(dptr)) != NULL;) {
                if (strcmp(ds->d_name, cmd_arr[0]) == 0) {
                    *filepath = mx_strjoin(token, "/");
                    *filepath = mx_strjoin(*filepath, ds->d_name); // need free in mx_strjoin;
                    return 2; // 2 means == type = binary;
                }
            }
        closedir(dptr);
        }
    }
    return -1;
}
