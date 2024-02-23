#include "../core/types.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <regex.h>

typedef struct {
    // Should be "IWAD" or "PWAD"
    char    identification[4];
    int32_t numlumps;
    int32_t infotableofs;
} wadinfo_t;

typedef struct {
    int32_t filepos;
    int32_t size;
    char    name[8];
} filelump_t;

// WADFILE I/O
typedef struct {
    char    name[8];
    int32_t handle;
    int32_t position;
    int32_t size;
} lumpinfo_t;

enum MAP_LUMPS {
    LABEL = 0,
    THINGS,
    LINEDEFS,
    SIDEDEFS,
    VERTEXES,
    SEGS,
    SSECTORS,
    NODES,
    SECTORS,
    REJECT,
    BLOCKMAP
};

bool read_wad_from_path(const char *file_path)
{
    int handle;
    wadinfo_t header;
    ssize_t bytes_read;
    off_t current_offset;
    filelump_t *directory = NULL;
    int numlumps;
    int map_count;
    Dynamic_Array maps;

    handle = open(file_path, O_RDONLY);
    if(handle == -1) {
        fprintf(stderr, "ERROR: failed to open file `%s`: %s\n", file_path, strerror(errno));
        return false;
    }

    bytes_read = read(handle, &header, sizeof(wadinfo_t));
    if(bytes_read == -1) {
        fprintf(stderr, "ERROR: failed to read header in file `%s`: %s\n", file_path, strerror(errno));
        goto defer;
    }

    numlumps = header.numlumps;

    current_offset = lseek(handle, header.infotableofs, SEEK_SET);
    if(current_offset == -1) {
        fprintf(stderr, "ERROR: failed to seek in file `%s`: %s\n", file_path, strerror(errno));
        goto defer;
    }

    directory = malloc(sizeof(filelump_t) * numlumps);
    if(directory == NULL) {
        fprintf(stderr, "ERROR: failed to allocate %zu bytes: %s\n", (sizeof(filelump_t) * numlumps), strerror(errno));
        goto defer;
    }

    bytes_read = read(handle, directory, (sizeof(filelump_t) * numlumps));
    if(bytes_read == -1) {
        fprintf(stderr, "ERROR: failed to read directory in file `%s`: %s\n", file_path, strerror(errno));
        goto defer;
    }

    // TODO: find maps in WAD file
    da_init(&maps, 32);
    for(int32_t i = 0; i < numlumps; ++i) {
        /* printf("%.8s\n", directory[i].name); */
        /* regex_t map_regex; */
        /* if(regcomp(&map_regex, "E[:number:]M[:number:]", 0) != 0) { */
        /*     fprintf(stderr, "ERROR: failed to compile regular expression\n"); */
        /*     goto defer; */
        /* } */

        /* int regexec(map_regex, const char *restrict string, */
        /*             size_t nmatch, regmatch_t pmatch[_Nullable restrict .nmatch], */
        /*             int eflags); */

        if(strncmp(directory[i].name, "E1M1", 8) == 0) {
            da_append(&maps, i);
        }
    }

    if(close(handle) == -1) {
        fprintf(stderr, "ERROR: failed to close file `%s`: %s\n", file_path, strerror(errno));
        return false;
    }

    free(directory);
    da_deallocate(&maps);
    return true;

defer:
    if(directory) free(directory);
    if(maps.array) da_deallocate(&maps);
    if(close(handle) == -1) {
        fprintf(stderr, "ERROR: failed to close file `%s`: %s\n", file_path, strerror(errno));
        return false;
    }
    return false;
}
