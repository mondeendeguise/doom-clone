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

struct File_Lump *read_directory(const char *path) {
    int wadfile;
    struct WAD_Header header;
    struct File_Lump *directory = {0};
    uint32_t numlumps;
    off_t infotableofs;
    size_t infotablesize;
    int s;

    header = read_header(path);

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

int32_t get_lump_index(const char *path, const char *lump_name) {
    struct WAD_Header header = read_header(path);
    struct File_Lump *directory = read_directory(path);
    int32_t numlumps = header.lump_count;

    for(int i = 0; i < numlumps; i++) {
        struct File_Lump lump = directory[i];
        if(strcasestr(lump.name, lump_name)) {
            return i;
        }
    }
    free(directory);
    return -1;
}

struct Vertex *read_vertices(const char *path, const char *map_name) {
    int wadfile;
    struct WAD_Header header = read_header(path);
    struct File_Lump *directory;
    struct Vertex *vertices;
    int s;

    directory = read_directory(path);
    int32_t numlumps = header.lump_count;

    enum LUMP_INDICES {
        LABEL     = 0,
        THINGS    = 1,
        LINEDEFS  = 2,
        SIDEDEFS  = 3,
        VERTEXES  = 4,
        SEGS      = 5,
        SSECTORS  = 6,
        NODES     = 7,
        SECTORS   = 8,
        REJECT    = 9,
        BLOCKMAP  = 10,
    };
    
    // Find map
    struct File_Lump map_vertices;
    for(int i = 0; i < numlumps; i++) {
        if((strcmp(directory[i].name, map_name)) == 0) {
            map_vertices = directory[i + VERTEXES];
            break;
        }
    }

    int32_t vertex_count = map_vertices.size / sizeof(struct Vertex);

    // Read
    wadfile = open(path, O_RDONLY);
    if(wadfile < 0) {
        FATAL("Failed to open file %s: %s", path, strerror(errno));
    }

    s = lseek(wadfile, map_vertices.pos, SEEK_SET);
    if(s == -1) {
        FATAL("Failed to seek in file %s: %s", path, strerror(errno));
    }

    vertices = malloc(map_vertices.size);
    for(int i = 0; i < vertex_count; i++) {
        s = read(wadfile, &vertices[i], sizeof(struct Vertex));
        if(s == -1) {
            FATAL("Failed to read from WAD: %s", strerror(errno));
        }
    }

    s = close(wadfile);
    if(s == -1) {
        FATAL("Failed to close file %s: %s", path, strerror(errno));
    }

    for(int i = 0; i < vertex_count; i++) {
        printf("%i, %i\n", vertices[i].x, vertices[i].y);
    }

    free(directory);
    return vertices;
}

struct WAD read_wad(const char *path) {
    struct WAD wad;
    struct WAD_Header header;
    struct File_Lump *directory;

    header = read_header(path);
    directory = read_directory(path);

    wad.header = header;
    wad.directory = directory;

    return wad;
}

void close_wad(struct WAD wad) {
    free(wad.directory);
}
