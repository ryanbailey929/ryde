//author Ryan Bailey

#include "main_window.hpp"

#include "base/window.hpp"
#include "colors.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>

MainWindow::MainWindow(std::string title, int width, int height)
                      : Window(title, width, height)
{

}

void MainWindow::update()
{    
    glfwPollEvents();

    glClearColor((Colors::side_panel_background_color[0]/255.0f),
                 (Colors::side_panel_background_color[1]/255.0f),
                 (Colors::side_panel_background_color[2]/255.0f),
                 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

void MainWindow::key_callback(int key, int action, int mods)
{

}

void MainWindow::char_callback(unsigned int codepoint)
{

}

void MainWindow::mouse_callback(int button, int action, int mods)
{

}

void MainWindow::cursor_callback(double x, double y)
{

}
