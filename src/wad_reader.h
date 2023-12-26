#pragma once

#include <fcntl.h>
#include <stdint.h>

struct WAD_Header {
    char wad_type[4];
    int32_t lump_count;
    int32_t directory_offset;
};

struct File_Lump {
    int32_t pos;
    int32_t size;
    char name[8];
};

struct WAD {
    struct WAD_Header header;
    struct File_Lump *directory;
};

struct WAD_Header read_header(int wadfile);
struct File_Lump *read_directory(int wadfile, int lump_count, off_t offset);

struct WAD read_wad(const char *path);

void open_wad(const char *path);
void close_wad(struct WAD wad);
