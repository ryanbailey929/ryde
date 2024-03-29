//author Ryan Bailey

#ifndef RYDE_WIDGETS_MAINAREA_HPP
#define RYDE_WIDGETS_MAINAREA_HPP

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

class MainWindow; //forward declaration to deal with circular dependency between
                  //MainArea and MainWindow

class MainArea : public Widget
{
    float x, y, width, height;
    MainWindow *main_window;
    inline static constexpr int separator_width {3};
    inline static unsigned int VAO, VBO, EBO;
    inline static bool VAO_VBO_EBO_and_shaders_generated {false};
    inline static unsigned int shader_program;
public:
    MainArea(float x, float y, float width, float height, float z,
             MainWindow *main_window);
    virtual void draw(glm::mat4 projection);
    virtual bool is_in_hitbox(int cursor_x, int cursor_y);
};

#endif
