//author Ryan Bailey

#ifndef RYDE_BASE_WINDOW_HPP
#define RYDE_BASE_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Window
{
protected:
    GLFWwindow *window;
public:
    Window(std::string title, int width, int height);
    virtual void update()=0;
    
    //the below functions are  called by GLFW
    virtual void key_callback(int key, int action, int mods) {}
    virtual void char_callback(unsigned int codepoint) {}
    virtual void mouse_callback(int button, int action, int mods) {}
    virtual void cursor_callback(double x, double y) {}

    bool should_close() {return glfwWindowShouldClose(window);}
};

#endif
