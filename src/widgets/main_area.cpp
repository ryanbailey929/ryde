//author Ryan Bailey

#include "main_area.hpp"

#include "../shaders/headers/basic_vertex_shader.hpp"
#include "../shaders/headers/main_area_fragment_shader.hpp"

#include "../main_window.hpp"
#include "../base/widget.hpp"
#include "../colors.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

MainArea::MainArea(float x, float y, float width, float height, float z,
                   MainWindow *main_window)
                  : x {x}, y {y}, width {width}, height {height},
                    main_window {main_window}
{
    set_offset(x, y);
    if(!VAO_VBO_EBO_and_shaders_generated)
    {
        float* vertices {create_quad_vertices(0, 0, width, height, z)};
        unsigned int* indices = {create_quad_indices()};
        generate_VAO_VBO_EBO(vertices, 12, indices, 6, VAO, VBO, EBO);
        unsigned int vertex_shader
            {create_shader(Shaders::Basic::vertex_shader_source,
                           ShaderType::VERTEX)};
        unsigned int fragment_shader
            {create_shader(Shaders::MainArea::fragment_shader_source,
                           ShaderType::FRAGMENT)};
        shader_program = create_program(vertex_shader, fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
}

void MainArea::draw(glm::mat4 projection)
{
    glUseProgram(shader_program);
    set_color_uniform_3D(glGetUniformLocation(shader_program,
                                              "main_area_background_color"),
                         Colors::main_area_background_color);
    set_color_uniform_3D(glGetUniformLocation(shader_program, "separator_color"),
                         Colors::separator_color);
    set_int_uniform_1D(glGetUniformLocation(shader_program, "separator_width"),
                       separator_width);
    set_vec_uniform_2D(glGetUniformLocation(shader_program, "bottom_left"), x, y);
    set_vec_uniform_2D(glGetUniformLocation(shader_program, "top_right"), x + width,
                       y + height);
    int height_diff {main_window->get_monitor_height() - main_window->get_height()};
    set_int_uniform_1D(glGetUniformLocation(shader_program, "height_diff"),
                       height_diff);
    set_matrix_uniform_4D(glGetUniformLocation(shader_program, "model"), model);
    set_matrix_uniform_4D(glGetUniformLocation(shader_program, "projection"),
                          projection);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

bool MainArea::is_in_hitbox(int cursor_x, int cursor_y)
{
    return is_in_rectangular_hitbox(cursor_x, cursor_y, x, y, width, height);
}
