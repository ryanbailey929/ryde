//author Ryan Bailey

#ifndef RYDE_BASE_WIDGET_HPP
#define RYDE_BASE_WIDGET_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <array>

enum class ShaderType
{
    VERTEX,
    FRAGMENT
};

class Widget
{
public:
    Widget()=default;
    virtual void draw(glm::mat4 projection)=0;
protected:
    glm::mat4 model {glm::mat4(1.0f)};

    void set_offset(float x, float y)
        {model = glm::translate(model, glm::vec3(x, y, 0.0f));}

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
    //generates and configures a VAO, VBO and EBO for the vertices and indices
    static void generate_VAO_VBO_EBO(float* vertices, int vertices_length,
                                     unsigned int* indices, int indices_length,
                                     unsigned int& VAO, unsigned int& VBO,
                                     unsigned int& EBO);
    //divides the elements of color_vec by 255, then set's color_uniform to the result.
    //glUseProgram should obviously be called before setting uniforms.
    //3D means color_vec has 3 Dimensions, and alpha should be set to 1.
    static void set_color_uniform_3D(int color_uniform, std::array<int, 3> color_vec);
    static void set_matrix_uniform_4D(int matrix_uniform, glm::mat4 matrix);
};

#endif
