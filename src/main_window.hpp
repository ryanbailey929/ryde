//author Ryan Bailey

#ifndef RYDE_MAINWINDOW_HPP
#define RYDE_MAINWINDOW_HPP

#include "base/window.hpp"
#include "colors.hpp"

#include "widgets/main_area.hpp"
#include "widgets/tab.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>
#include <memory>

//forward declarations to deal with circular dependencies
class MainArea;
class Tab;

class MainWindow : public Window
{
    glm::mat4 projection {1.0f};
    std::unique_ptr<MainArea> main_area;
    std::unique_ptr<Tab> tab_1;
    float main_area_x, main_area_y, main_area_width, main_area_height;
    int cursor_x, cursor_y;

    void handle_events();
public:
    MainWindow(std::string title, int width, int height);
    virtual void update();
    virtual void update_projection();
};

//a namespace containing a Z value for every widget in the main window.
//furthest back values first, furthest forward values last.
namespace MainWindowZ
{
    inline float MAX_Z {1000.0f};

    inline float MAIN_AREA {900.0f};
    inline float TAB_AT_REST {900.0f};
    inline float TAB_BEING_MOVED {899.0f};

    inline float MIN_Z {1.0f};
};

#endif
