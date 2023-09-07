//author Ryan Bailey

#include "main_window.hpp"

#include <iostream>

int main()
{
    MainWindow *main_window;
    try
    {
        main_window = new MainWindow("RyDE version: 0.1", 960, 540);
    }
    catch(...)
    {
        std::cerr << "Error in creating window. Exiting.\n";
        return 0;
    }
    while(!main_window->should_close())
    {
        while(!MainWindow::time_for_next_update()); //limit the ups
        main_window->update();
    }
    
    return 0;
}
