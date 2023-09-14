//author Ryan Bailey

#include "main_area.hpp"

#include "../base/widget.hpp"
#include "../colors.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

MainArea::MainArea(float x, float y, float width, float height, float z)
{
    std::string vertex_shader_source
    {
        "#version 330 core\n"
        "layout (location = 0) in vec3 a_pos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projection * model * vec4(a_pos, 1.0f);\n"
        "}"
    };
    std::string fragment_shader_source
    {
        "#version 330 core\n"
        "uniform vec3 color;\n"
        "out vec4 frag_color;\n"
        "void main()\n"
        "{\n"
        "    frag_color = vec4(color, 1.0f);\n"
        "}"
    };
    set_offset(x, y);
    if(!VAO_VBO_EBO_and_shaders_generated)
    {
        float* vertices {create_quad_vertices(0, 0, width, height, z)};
        unsigned int* indices = {create_quad_indices()};
        generate_VAO_VBO_EBO(vertices, 12, indices, 6, VAO, VBO, EBO);
        unsigned int vertex_shader {create_shader(vertex_shader_source,
                                                  ShaderType::VERTEX)};
        unsigned int fragment_shader {create_shader(fragment_shader_source,
                                                    ShaderType::FRAGMENT)};
        shader_program = create_program(vertex_shader, fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
}

void MainArea::draw(glm::mat4 projection)
{
    glUseProgram(shader_program);
    set_color_uniform_3D(glGetUniformLocation(shader_program, "color"),
                         Colors::main_area_background_color);
    set_matrix_uniform_4D(glGetUniformLocation(shader_program, "model"), model);
    set_matrix_uniform_4D(glGetUniformLocation(shader_program, "projection"),
                          projection);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
