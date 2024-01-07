#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/logger.h"
#include "wad_reader.h"
#include "lump.h"

#define DEFAULT_WAD "wad/DOOM.WAD"

int main(int argc, char *argv[]) {
    char *wadpath;

    const char *usage = "Usage: %s <WAD>\n";

    if(argc >= 2) {
        if(strcmp(argv[1], "-h") == 0) {
            fprintf(stderr, "%s\n", usage);
            exit(EXIT_SUCCESS);
        }

        wadpath = argv[1];
    } else {
        INFO("No WAD specified. Using default: %s", DEFAULT_WAD);
        wadpath = DEFAULT_WAD;
    }

    struct WAD wad = read_wad(wadpath);

    struct Vertex *vertices = read_vertices(wadpath, "E1M1");

    /* int32_t name_index = get_lump_index(wadpath, "E1M1"); */
    /* printf("E1M1: %i\n", name_index); */

    close_wad(wad);
    return 0;
}
