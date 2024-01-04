#pragma once

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

