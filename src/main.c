#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/logger.h"
#include "core/filesystem.h"
#include "wad_reader.h"
#include "render.h"

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

    // WAD is in RAM, now we can start rendering
    r_init_glfw();

    /* GLuint vertex_buffer; */
    /* glGenBuffers(1, &vertex_buffer); */
    /* glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer); */
    /* glBufferData(GL_ARRAY_BUFFER, vertex_count * 2 * sizeof(int16_t), vertices, GL_STATIC_DRAW); */

    /* glEnableVertexAttribArray(0); */
    /* glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, sizeof(int16_t), 0); */

    const char *shader_vertex_source = buffer_file(SHADER_PATH "basic.vert.shader");
    const char *shader_fragment_source = buffer_file(SHADER_PATH "basic.frag.shader");
    struct Shader_Source shader_source = { shader_vertex_source, shader_fragment_source };

    GLFWwindow *window = r_create_window(640, 480, "DOOM");
    unsigned int shader = r_init_shaders(shader_source);

    int32_t vertex_count = get_vertex_count(wadpath, "E1M1");
    struct Vec2D *vertices = (struct Vec2D *) read_vertices(wadpath, "E1M1");
    r_load_vertices(vertices, vertex_count * 2 * sizeof(int16_t));

    /**
    * MAIN RENDERING LOOP
    */
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    close_wad(wad);
    return 0;
}
