//author Ryan Bailey

#include "main_window.hpp"

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

MainWindow::MainWindow(std::string title, int width, int height)
                      : Window(title, width, height)
{
    main_area_x = monitor_width*(1/8.0f);
    main_area_y = 0;
    main_area_width = monitor_width*(7/8.0f);
    main_area_height = monitor_height*(9.6f/10.0f);

    main_area = std::unique_ptr<MainArea> {new MainArea
        {main_area_x, main_area_y, main_area_width, main_area_height,
         MainWindowZ::MAIN_AREA, this}};

    tab_1 = std::unique_ptr<Tab> {new Tab {main_area_x, main_area_height,
                                           200, monitor_height - main_area_height,
                                           MainWindowZ::TAB_AT_REST, this}};

    projection = glm::ortho(0.0f, (float) width, (float) monitor_height - height,
                            (float) monitor_height, -MainWindowZ::MIN_Z,
                            -MainWindowZ::MAX_Z);
}

void MainWindow::update()
{
    glfwPollEvents();

    if(event_has_occured)
    {
        handle_events();
        event_has_occured = false;
    }

    glClearColor((Colors::side_panel_background_color[0]/255.0f),
                 (Colors::side_panel_background_color[1]/255.0f),
                 (Colors::side_panel_background_color[2]/255.0f),
                 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    main_area->draw(projection);
    tab_1->draw(projection);

    glfwSwapBuffers(window);
}

void MainWindow::update_projection()
{
    projection = glm::ortho(0.0f, (float) width, (float) monitor_height - height,
                            (float) monitor_height, -MainWindowZ::MIN_Z,
                            -MainWindowZ::MAX_Z);
}

void MainWindow::handle_events()
{
    //only the last cursor event registered between updates is necessary, so we
    //only keep the last one (I don't even know if multiple cursor updates per
    //window update is a thing, but I'm doing it this way just in case).
    //We put it first so that all events after it will use the correct cursor location.
    if(cursor_event) //only add the cursor event if there is one
        events.push_front(cursor_event);
    for(std::list<Event*>::iterator e_it {events.begin()}; e_it != events.end(); ++e_it)
    {
        if((*e_it)->get_type() == EventType::CURSOR)
        {
            cursor_x = (int) ((CursorEvent*) (*e_it))->get_x();
            cursor_y = (int) ((CursorEvent*) (*e_it))->get_y();
        }
        if(main_area->is_in_hitbox(cursor_x, cursor_y))
        {
            std::cout << "[Main Area] ";
            print_event((*e_it));
        }
        if(tab_1->is_in_hitbox(cursor_x, cursor_y))
        {
            std::cout << "[Tab 1] ";
            print_event((*e_it));
        }
    }
    cursor_event = nullptr;
    events.clear();
}
