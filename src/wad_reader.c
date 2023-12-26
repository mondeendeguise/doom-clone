#include "wad_reader.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/logger.h"

struct WAD_Header read_header(int wadfile) {
    struct WAD_Header header;

    read(wadfile, &header.wad_type, 4); // ascii - IWAD or PWAD
    read(wadfile, &header.lump_count, 4);
    read(wadfile, &header.directory_offset, 4);
    return header;
}

struct File_Lump *read_directory(int wadfile, int lump_count, off_t offset) {
    struct File_Lump *directory = malloc(sizeof(struct File_Lump) * lump_count);
    lseek(wadfile, offset, SEEK_SET);
    for(int i = 0; i < lump_count; i++) {
        struct File_Lump lump = {0};
        read(wadfile, &lump.pos, 4);
        read(wadfile, &lump.size, 4);
        char n[9];
        read(wadfile, n, 8);
        n[8] = 0;
        strncpy(lump.name, n, 8);
        /* read(wadfile, &lump, sizeof(struct File_Lump)); */
        if(i < 25) printf("%s\n",n);
        directory[i] = lump;
    }

    return directory;
}

struct WAD read_wad(const char *path) {
    int wadfile;
    struct WAD wad;

    wadfile = open(path, O_RDONLY);

    wad.header = read_header(wadfile);
    wad.directory = read_directory(wadfile, wad.header.lump_count,
                                   wad.header.directory_offset);

    close(wadfile);
    return wad;
}

void open_wad(const char *path) {
    int wadfile;
    struct WAD_Header header;
    uint32_t numlumps;
    uint32_t infotableofs;
    struct File_Lump *directory;
    size_t infotablesize;
    
    wadfile = open(path, O_RDONLY);

    read(wadfile, &header, sizeof(header));

    if(strncmp(header.wad_type, "IWAD", 4)) {
        WARN("wadfile has a weirdo header");
    }

    numlumps = header.lump_count;
    infotableofs = header.directory_offset;
    infotablesize = sizeof(struct File_Lump) * numlumps;

    directory = malloc(infotablesize);
    lseek(wadfile, infotableofs, SEEK_SET);
    read(wadfile, directory, infotablesize);

    for(int i = 0; i < numlumps/50; i++) {
        printf("%.8s\n", directory[i].name);
    }

    // Are we done reading from the file?
    close(wadfile);

    free(directory);
}

void close_wad(struct WAD wad) {
    free(wad.directory);
}
