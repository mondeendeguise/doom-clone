#include "wad_reader.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "core/logger.h"

struct WAD_Header read_header(const char *path) {
    int wadfile;
    struct WAD_Header header;
    int s;

    wadfile = open(path, O_RDONLY);
    if(wadfile < 0) {
        int e = errno;
        FATAL("Failed to open file %s: %s", path, strerror(e));
        exit(EXIT_FAILURE);
    }

    s = read(wadfile, &header, sizeof(header));
    if(s == -1) {
        int e = errno;
        FATAL("Failed to read from WAD: %s", strerror(e));
        exit(EXIT_FAILURE);
    }

    s = close(wadfile);
    if(s == -1) {
        int e = errno;
        FATAL("Failed to close file %s: %s", path, strerror(e));
        exit(EXIT_FAILURE);
    }

    return header;
}

struct File_Lump *read_directory(const char *path, const struct WAD_Header header) {
    int wadfile;
    struct File_Lump *directory = {0};
    uint32_t numlumps;
    off_t infotableofs;
    size_t infotablesize;
    int s;

    wadfile = open(path, O_RDONLY);
    if(wadfile < 0) {
        int e = errno;
        FATAL("Failed to open file %s: %s", path, strerror(e));
        exit(EXIT_FAILURE);
    }

    numlumps = header.lump_count;
    infotableofs = header.directory_offset;
    infotablesize = numlumps * sizeof(struct File_Lump);

    directory = malloc(infotablesize);
    if(directory == NULL) {
        int e = errno;
        FATAL("Failed to allocate %d bytes: %s", infotablesize, strerror(e));
        exit(EXIT_FAILURE);
    }

    s = lseek(wadfile, infotableofs, SEEK_SET);
    if(s == -1) {
        int e = errno;
        FATAL("Failed to seek in file %s: %s", path, strerror(e));
        exit(EXIT_FAILURE);
    }

    /*
     * BE CAREFUL HERE!!!!
     * NOT ALL STRINGS STORED IN THE DIRECTORY ARE NULL TERMINATED
     * LIMIT THE AMOUNT YOURE READING FROM THEM
     */
    s = read(wadfile, directory, infotablesize);
    if(s == -1) {
        int e = errno;
        FATAL("Failed to read from WAD: %s", strerror(e));
        exit(EXIT_FAILURE);
    }

    s = close(wadfile);
    if(s == -1) {
        int e = errno;
        FATAL("Failed to close file %s: %s", path, strerror(e));
        exit(EXIT_FAILURE);
    }

    return directory;
}

struct WAD read_wad(const char *path) {
    struct WAD wad;
    struct WAD_Header header;
    struct File_Lump *directory;

    header = read_header(path);
    directory = read_directory(path, header);

    wad.header = header;
    wad.directory = directory;

    return wad;
}

void close_wad(struct WAD wad) {
    free(wad.directory);
}
