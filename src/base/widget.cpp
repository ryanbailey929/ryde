//author Ryan Bailey

#include "widget.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <array>

unsigned int Widget::create_shader(std::string shader_source, ShaderType shader_type)
{
    unsigned int shader;
    if(shader_type == ShaderType::VERTEX)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else //shader_type == ShaderType::FRAGMENT
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* shader_source_c_str {shader_source.c_str()};
    glShaderSource(shader, 1, &shader_source_c_str, nullptr);
    glCompileShader(shader);
    compile_check(shader, shader_type);
    return shader;
}

unsigned int Widget::create_program(unsigned int vertex_shader,
                                    unsigned int fragment_shader)
{
    unsigned int shader_program {glCreateProgram()};
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    link_check(shader_program);
    return shader_program;
}

void Widget::compile_check(unsigned int shader, ShaderType shader_type)
{
    char info_log[512];
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        if(shader_type == ShaderType::VERTEX)
            std::cerr << "Vertex";
        else //shader_type == ShaderType::FRAGMENT
            std::cerr << "Fragment";
        std::cerr << " shader compilation failed. Details: " << info_log << '\n';
        throw -1;
    }
}

void Widget::link_check(unsigned int shader_program)
{
    char info_log[512];
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cerr << "Shader program linking failed. Details: " << info_log << '\n';
        throw -1;
    }
}

float* Widget::create_quad_vertices(float x, float y, float width, float height,
                                   float z)
{
    return new float[12] { x,         y,          z,
                           x + width, y,          z,
                           x + width, y + height, z,
                           x,         y + height, z};
}

unsigned int* Widget::create_quad_indices()
{
    return new unsigned int[6] {1, 2, 3,
                                0, 1, 3};
}

void Widget::set_offset(float x, float y)
{
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
}

void Widget::set_color_uniform_3D(int color_uniform, std::array<int, 3> color_vec)
{
    glUniform3f(color_uniform,
                color_vec[0]/255.0f, color_vec[1]/255.0f, color_vec[2]/255.0f);
}

void Widget::set_matrix_uniform_4D(int matrix_uniform, glm::mat4 matrix)
{
    glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Widget::set_vec_uniform_2D(int uniform, float one, float two)
{
    glUniform2f(uniform, one, two);
}

void Widget::set_int_uniform_1D(int uniform, int one)
{
    glUniform1i(uniform, one);
}

void Widget::generate_VAO_VBO_EBO(float* vertices, int vertices_length,
                                  unsigned int* indices, int indices_length,
                                  unsigned int& VAO, unsigned int& VBO,
                                  unsigned int& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_length*sizeof(float), vertices,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length*sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    delete[] vertices;
    delete[] indices;
}
