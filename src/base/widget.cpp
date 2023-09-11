//author Ryan Bailey

#include "widget.hpp"

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

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
    glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cerr << "Shader program linking failed. Details: " << info_log << '\n';
        throw -1;
    }
}

float* create_quad_vertices(float x, float y, float width, float height,
                                   float z)
{
    return new float[12] { x,         y,          z,
                           x + width, y,          z,
                           x + width, y + height, z,
                           x,         y + height, z};
}

unsigned int* create_quad_indices()
{
    return new unsigned int[6] {0, 1, 2,
                                1, 3, 2};
}
