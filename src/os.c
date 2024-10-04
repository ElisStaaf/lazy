#include "lazy.h"
#include <stdlib.h>

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    #define OS "posix"
#else
    #define OS "nt"
#endif

char * osName() { return OS }

int osClear() {
    if (osName() == "posix") {
        osSystem("clear");
    } else if (osName() == "nt") {
        osSystem("cls");
    }
    return 0;
}

int osPwd() {
    if (osName() == "posix") {
        osSystem("pwd");
    } else if (osName() == "posix") {
        osSystem("ECHO %CD%");
    }
    return 0;
}

int osSystem(char cmd[]) {
    system(cmd);
    return 0;
}

FILE osRead(char filename[], char mode[]) {
    FILE *file;
    file = fopen(filename, mode);
    return file;
}

int osWriteTo(char msg[], char filename[]) {
    osSystem("\"%s\" >> \"%s\"", msg, filename);
    return 0;
}

int osListDir(char dir="pwd") {
    osSystem("ls %s", dir);
    return 0;
}
