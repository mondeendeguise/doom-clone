#include "map.h"

#include <stdlib.h>

#include "wad_reader.h"
#include "render.h"

struct Bounds {
    struct Vec2D min;
    struct Vec2D max;
};

struct Bounds get_map_bounds(const char *path, const char *map_name) {
    struct Vec2D *vertices = (struct Vec2D *) read_vertices(path, map_name);
    int32_t vertex_count = get_vertex_count(path, map_name);
    int16_t minx, miny;
    int16_t maxx, maxy;
    minx = vertices[0].x;
    miny = vertices[0].y;
    maxx = vertices[0].x;
    maxy = vertices[0].y;

    for(int i = 1; i < vertex_count; i++) {
        if(vertices[i].x > maxx) {
            maxx = vertices[i].x;
        } else if(vertices[i].x < minx) {
            minx = vertices[i].x;
        }

        if(vertices[i].y > maxy) {
            maxy = vertices[i].y;
        } else if(vertices[i].y < miny) {
            miny = vertices[i].y;
        }
    }

    struct Vec2D min = { minx, miny };
    struct Vec2D max = { maxx, maxy };
    struct Bounds ret = { min, max };
    return ret;
}
