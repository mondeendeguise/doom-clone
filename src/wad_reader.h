#pragma once

#include "wad.h"
#include "lump.h"

int32_t get_lump_index(const char *path, const char *lump_name);
struct Vertex *read_vertices(const char *path, const char *map_name);
struct WAD read_wad(const char *path);
void close_wad(struct WAD wad);
