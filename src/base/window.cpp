//author Ryan Bailey

#include "window.hpp"

#include "event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <list>

Window::Window(std::string title, int width, int height)
              : width {width}, height {height}
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
            ((Window*) glfwGetWindowUserPointer(window))->width = width;
            ((Window*) glfwGetWindowUserPointer(window))->height = height;
            ((Window*) glfwGetWindowUserPointer(window))->update_projection();
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
    glfwSetScrollCallback(window,
        [] (GLFWwindow *window, double x, double y)
        {
            ((Window*) glfwGetWindowUserPointer(window))->scroll_callback(x, y);
        });
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //this sets monitor_width and monitor_height
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &monitor_width,
                           &monitor_height);
}

bool Window::should_close()
{
    return glfwWindowShouldClose(window);
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

void Window::key_callback(int key, int action, int mods)
{
    events.push_back(new KeyEvent(key, action, mods));
    event_has_occured = true;
}

void Window::char_callback(unsigned int codepoint)
{
    events.push_back(new CharEvent(codepoint));
    event_has_occured = true;
}

void Window::mouse_callback(int button, int action, int mods)
{
    events.push_back(new MouseEvent(button, action, mods));
    event_has_occured = true;
}

void Window::cursor_callback(double x, double y)
{
    cursor_event = new CursorEvent(x, monitor_height - y);
    event_has_occured = true;
}

void Window::scroll_callback(double x, double y)
{
    events.push_back(new ScrollEvent(x, y));
    event_has_occured = true;
}

int Window::get_width()
{
    return width;
}

int Window::get_height()
{
    return height;
}

int Window::get_monitor_width()
{
    return monitor_width;
}

int Window::get_monitor_height()
{
    return monitor_height;
}
