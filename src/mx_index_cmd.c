#include "ush.h"

int mx_index_cmd(char **cmd) {
    int flag = 0;
    int len;

    for (int index = 0; cmd[index]; index++) {
        len = mx_strlen(cmd[index]);
        if (cmd[index][0] != '\'' && cmd[index][0] != '"' && cmd[index][0] != '=') { // 85 characte
            for (int j = 1; j < len; j++) {
                if (cmd[index][j] == '=') {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) {
                flag = 0;
                continue;
            }
        }
        return index;
    }
    return -1;
}
