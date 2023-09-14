//author Ryan Bailey

#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

Window::Window(std::string title, int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!window)
    {
        glfwTerminate();
        std::cerr << "[Window::Window] Failed to create window.";
        throw -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
         glfwTerminate();
         std::cerr << "[Window::Window] Failed to initialise GLAD.";
         throw -1;
    }

    glViewport(0, 0, width, height);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window,
        [] (GLFWwindow *window, int width, int height)
        {
            glViewport(0, 0, width, height);
            ((Window*) glfwGetWindowUserPointer(window))->update_projection(width,
                                                                            height);
        });
    glfwSetKeyCallback(window,
        [] (GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            ((Window*) glfwGetWindowUserPointer(window))->key_callback(key, action,
                                                                       mods);
        });
    glfwSetCharCallback(window,
        [] (GLFWwindow *window, unsigned int codepoint)
        {
            ((Window*) glfwGetWindowUserPointer(window))->char_callback(codepoint);
        });
    glfwSetMouseButtonCallback(window,
        [] (GLFWwindow *window, int button, int action, int mods)
        {
            ((Window*) glfwGetWindowUserPointer(window))->mouse_callback(button, action,
                                                                        mods);
        });
    glfwSetCursorPosCallback(window,
        [] (GLFWwindow *window, double x, double y)
        {
            ((Window*) glfwGetWindowUserPointer(window))->cursor_callback(x, y);
        });
    glEnable(GL_DEPTH_TEST);
}

bool Window::time_for_next_update()
{
    double current_time = glfwGetTime();
    if(current_time >= (time_of_last_frame + (1.0f/ups)))
    {
        time_of_last_frame = current_time;
        return true;
    }
    return false;
}
