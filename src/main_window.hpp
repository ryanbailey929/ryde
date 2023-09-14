//author Ryan Bailey

#ifndef RYDE_MAINWINDOW_HPP
#define RYDE_MAINWINDOW_HPP

#include "base/window.hpp"
#include "colors.hpp"

#include "widgets/main_area.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <array>
#include <memory>

class MainWindow : public Window
{
    glm::mat4 projection {1.0f};
    std::unique_ptr<MainArea> main_area;
    float main_area_x, main_area_y, main_area_width, main_area_height;

    //monitor_width and monitor_height are in screen coords, as is width and height.

    //monitor_width and monitor_height technically aren't the width and height of the
    //monitor, but the width and height of the work area of that monitor, i.e. the part
    //of it where the window would go. So it doesn't include things like desktop
    //environment toolbars. That's good. We only want the work area, as we don't want
    //to place the window over any toolbars. Just bear in mind, while monitor_width and
    //monitor_height are clear _enough_ names to use here, technically they only contain
    //the monitor work area.
    int monitor_width, monitor_height;
public:
    MainWindow(std::string title, int width, int height);
    virtual void update();
    virtual void update_projection(int width, int height);
    virtual void key_callback(int key, int action, int mods);
    virtual void char_callback(unsigned int codepoint);
    virtual void mouse_callback(int button, int action, int mods);
    virtual void cursor_callback(double x, double y);
};

//a namespace containing a Z value for every widget in the main window.
//furthest back values first, furthest forward values last.
namespace MainWindowZ
{
    inline float MAX_Z {1000.0f};

    inline float MAIN_AREA {900.0f};

    inline float MIN_Z {1.0f};
};

#endif
