//
// Created by hausa on 11/2/2022.
//

#include <cstring>

int parseCommand(char* cmd) {
    if (strcmp(cmd, "quit") == 0) {
        return 0;
    } else {
        return 1;
    }
}

