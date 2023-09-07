//author Ryan Bailey

#ifndef RYDE_MAINWINDOW_HPP
#define RYDE_MAINWINDOW_HPP

#include "base/window.hpp"
#include "colors.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>

class MainWindow : public Window
{
public:
    MainWindow(std::string title, int width, int height);
    void update();
    virtual void key_callback(int key, int action, int mods);
    virtual void char_callback(unsigned int codepoint);
    virtual void mouse_callback(int button, int action, int mods);
    virtual void cursor_callback(double x, double y);
};

#endif
