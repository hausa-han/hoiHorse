//
// Created by hausa on 10/30/2022.
//
#include "localLog.h"

bool logError(char* msg) {
    std::cout << "ERROR: " << msg << std::endl;
    return true;
}

bool logMessage(char* msg) {
    std::cout << "RUN TIME: " << msg << std::endl;
    return true;
}
