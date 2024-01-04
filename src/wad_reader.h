#pragma once

#include "wad.h"

struct WAD read_wad(const char *path);
void close_wad(struct WAD wad);
