//author Ryan Bailey

#ifndef RYDE_BASE_WIDGET_HPP
#define RYDE_BASE_WIDGET_HPP

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

enum class ShaderType
{
    VERTEX,
    FRAGMENT
};

class Widget
{
    glm::mat4 model {glm::mat4(1.0f)};
public:
    Widget()=default;
    virtual void draw()=0;
protected:
    static unsigned int create_shader(std::string shader_source,
                                      ShaderType shader_type);
    static unsigned int create_program(unsigned int vertex_shader,
                                       unsigned int fragment_shader);
    static void compile_check(unsigned int shader, ShaderType shader_type);
    static void link_check(unsigned int shader_program);

    //will produce the 4 vertices (12 floats), needed to create a quad defined by x, y,
    //width and height at the given z. Quad is in the x-y plane, obviously.
    static float* create_quad_vertices(float x, float y, float width, float height,
                                       float z);
    //will produce the 6 indices (6 unsigned ints) for the vertices produced by
    //create_quad_vertices.
    static unsigned int* create_quad_indices();
};

#endif
