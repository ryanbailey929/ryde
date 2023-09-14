//author Ryan Bailey

#ifndef RYDE_BASE_WINDOW_HPP
#define RYDE_BASE_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Window
{
    static constexpr int ups {60}; //how many times the window will update per second
    inline static double time_of_last_frame {0};
protected:
    GLFWwindow *window;
public:
    Window(std::string title, int width, int height);
    virtual void update()=0;
    virtual void update_projection(int width, int height)=0;
    
    //the below functions are  called by GLFW
    virtual void key_callback(int key, int action, int mods) {}
    virtual void char_callback(unsigned int codepoint) {}
    virtual void mouse_callback(int button, int action, int mods) {}
    virtual void cursor_callback(double x, double y) {}

    bool should_close() {return glfwWindowShouldClose(window);}
    static bool time_for_next_update();
};

#endif
