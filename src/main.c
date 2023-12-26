#include <stdio.h>

#include "wad_reader.h"

int main(int argc, char *argv[]) {
    /* struct WAD wad = read_wad("wad/DOOM.WAD"); */
    /* struct WAD_Header header = wad.header; */

    /* printf("# Header #\n"); */
    /* printf("ID: %s\nLump Count: %d\nDirectory Offset: %d\n\n", */
    /*        header.wad_type, header.lump_count, header.directory_offset); */

    /* printf("# Directory #\n"); */
    /* for(int i = 0; i < header.lump_count/50; i++) { */
    /*     printf("{'offset': %d, 'size': %d, 'name': '%s'}\n", */
    /*            wad.directory[i].offset, wad.directory[i].size, */
    /*            wad.directory[i].name); */
    /* } */

    /* close_wad(wad); */
    open_wad("wad/DOOM.WAD");
    return 0;
}
