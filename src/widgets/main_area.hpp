//author Ryan Bailey

#ifndef RYDE_WIDGETS_MAINAREA_HPP
#define RYDE_WIDGETS_MAINAREA_HPP

#include "../shaders/headers/basic_vertex_shader.hpp"
#include "../shaders/headers/basic_fragment_shader.hpp"

#include "../base/widget.hpp"
#include "../colors.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class MainArea : public Widget
{
    inline static unsigned int VAO, VBO, EBO;
    inline static bool VAO_VBO_EBO_and_shaders_generated {false};
    inline static unsigned int shader_program;
public:
    MainArea(float x, float y, float width, float height, float z);
    void draw(glm::mat4 projection);
};

#endif
