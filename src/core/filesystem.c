#include "filesystem.h"
#include "logger.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

char *buffer_file(const char *path) {
    FILE *f;
    char *buffer;
    long length;

    int s;

    f = fopen(path, "rb");
    if(f == NULL) {
        ERROR("Failed to open file %s: %s", path, strerror(errno));
    }

    s = fseek(f, 0, SEEK_END);
    if(s != 0) {
        ERROR("Failed to seek in file %s: %s", path, strerror(errno));
    }

    length = ftell(f);
    if(length == -1) {
        ERROR("Failed to get offset in file %s: %s", path, strerror(errno));
    }

    s = fseek(f, 0, SEEK_SET);
    if(s != 0) {
        ERROR("Failed to seek in file %s: %s", path, strerror(errno));
    }

    buffer = malloc(length);
    if(buffer == NULL) {
        ERROR("Failed to allocate memory: %s", strerror(errno));
    }

    fread(buffer, 1, length, f);

    s = fclose(f);
    if(s != 0) {
        ERROR("Failed to close file: %s", strerror(errno));
    }

    return buffer;
}

void delete_buffer(char *buffer) {
    free(buffer);
}
