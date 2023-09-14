//author Ryan Bailey

#ifndef RYDE_WIDGETS_MAINAREA_HPP
#define RYDE_WIDGETS_MAINAREA_HPP

#include "../base/widget.hpp"
#include "../colors.hpp"

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
