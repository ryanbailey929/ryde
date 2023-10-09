//author Ryan Bailey

#ifndef RYDE_BASE_WINDOW_HPP
#define RYDE_BASE_WINDOW_HPP

#include "event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <list>

class Window
{
    static constexpr int ups {60}; //how many times the window will update per second
    inline static double time_of_last_frame {0};
protected:
    GLFWwindow *window;

    //monitor_width and monitor_height are in screen coords, as is width and height.

    //monitor_width and monitor_height technically aren't the width and height of the
    //monitor, but the width and height of the work area of that monitor, i.e. the part
    //of it where the window would go. So it doesn't include things like desktop
    //environment toolbars. That's good. We only want the work area, as we don't want
    //to place the window over any toolbars. Just bear in mind, while monitor_width and
    //monitor_height are clear _enough_ names to use here, technically they only contain
    //the monitor work area.
    int width, height, monitor_width, monitor_height;
    Event* cursor_event;
    std::list<Event*> events;
    bool event_has_occured {false};
public:
    Window(std::string title, int width, int height);
    virtual void update()=0;
    //you can use width and height when updating projection, as they are set just before
    //update_projection is called.
    virtual void update_projection()=0;
    
    //the below functions are called by GLFW
    void key_callback(int key, int action, int mods);
    void char_callback(unsigned int codepoint);
    void mouse_callback(int button, int action, int mods);
    void cursor_callback(double x, double y);
    void scroll_callback(double x, double y);
    //functions below here aren't called by GLFW

    bool should_close();
    static bool time_for_next_update();

    int get_width();
    int get_height();
    int get_monitor_width();
    int get_monitor_height();
};

#endif
