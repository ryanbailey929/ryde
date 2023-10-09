//author Ryan Bailey

#include "event.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//---------Event---------

EventType Event::get_type()
{
    return type;
}

//---------MouseKeyBaseEvent---------

MouseKeyBaseEvent::MouseKeyBaseEvent(int action, int mods)
                                    : action {action}, mods {mods} {}

int MouseKeyBaseEvent::get_action()
{
    return action;
}

int MouseKeyBaseEvent::get_mods()
{
    return mods;
}

//---------CursorScrollBaseEvent---------

CursorScrollBaseEvent::CursorScrollBaseEvent(double x, double y) : x {x}, y {y} {}

double CursorScrollBaseEvent::get_x()
{
    return x;
}

double CursorScrollBaseEvent::get_y()
{
    return y;
}

//---------MouseEvent---------

MouseEvent::MouseEvent(int button, int action, int mods)
                      : MouseKeyBaseEvent(action, mods), button {button}
{
    type = EventType::MOUSE;
}

int MouseEvent::get_button()
{
    return button;
}

//---------KeyEvent---------

KeyEvent::KeyEvent(int key, int action, int mods)
                  : MouseKeyBaseEvent(action, mods), key {key}
{
    type = EventType::KEY;
}

int KeyEvent::get_key()
{
    return key;
}

//---------CursorEvent---------

CursorEvent::CursorEvent(double x, double y) : CursorScrollBaseEvent(x, y)
{
    type = EventType::CURSOR;
}

//---------ScrollEvent---------

ScrollEvent::ScrollEvent(double x, double y) : CursorScrollBaseEvent(x, y)
{
    type = EventType::SCROLL;
}

//---------CharEvent---------

CharEvent::CharEvent(unsigned int codepoint) : codepoint {codepoint}
{
    type = EventType::CHAR;
}

unsigned int CharEvent::get_codepoint()
{
    return codepoint;
}

//---------print_event---------

#ifndef NDEBUG

//for debugging purposes
void print_event(Event *event)
{
    if(event->get_type() == EventType::CURSOR)
    {
        CursorEvent *cursor_event {(CursorEvent*) event};
        std::cout << "Cursor Event! x: " << cursor_event->get_x() << ", y: "
                  << cursor_event->get_y() << "\n";
    }
    else if(event->get_type() == EventType::MOUSE)
    {
        MouseEvent *mouse_event {(MouseEvent*) event};
        std::cout << "Mouse Event! ";
        if(mouse_event->get_button() == GLFW_MOUSE_BUTTON_LEFT)
            std::cout << "Left Mouse Button ";
        else if(mouse_event->get_button() == GLFW_MOUSE_BUTTON_RIGHT)
            std::cout << "Right Mouse Button ";
        else if(mouse_event->get_button() == GLFW_MOUSE_BUTTON_MIDDLE)
            std::cout << "Middle Mouse Button ";
        PrintEventFunctions::print_action(mouse_event->get_action());
        std::cout << ". ";
        PrintEventFunctions::print_mods(mouse_event->get_mods());
        std::cout << "\n";
    }
    else if(event->get_type() == EventType::KEY)
    {
        KeyEvent *key_event {(KeyEvent*) event};
        const char* key {glfwGetKeyName(key_event->get_key(),
                                        glfwGetKeyScancode(key_event->get_key()))};
        if(key)
            std::cout << "Key Event! Key: " << key << " ";
        else
            std::cout << "Key Event! Key: (not printable using glfwGetKeyName) ";
        PrintEventFunctions::print_action(key_event->get_action());
        std::cout << ". ";
        PrintEventFunctions::print_mods(key_event->get_mods());
        std::cout << "\n";
    }
    else if(event->get_type() == EventType::SCROLL)
    {
        ScrollEvent *scroll_event {(ScrollEvent*) event};
        std::cout << "Scroll Event! ";
        if(scroll_event->get_y() > 0)
            std::cout << "Scrolled Up.\n";
        else
            std::cout << "Scrolled Down.\n";
    }
    else if(event->get_type() == EventType::CHAR)
    {
        CharEvent *char_event {(CharEvent*) event};
        std::wcout << "Char Event! " << ((wchar_t) char_event->get_codepoint()) << "\n";
    }
}

namespace PrintEventFunctions
{
    void print_action(int action)
    {
        if(action == GLFW_PRESS)
            std::cout << "Pressed";
        else //action == GLFW_RELEASE
            std::cout << "Released";
    }
    
    void print_mods(int mods)
    {
        bool mod_pressed {false};
        std::cout << "Mods: ";
        if(mods & GLFW_MOD_CONTROL)
        {
            std::cout << "Ctrl ";
            mod_pressed = true;
        }
        if(mods & GLFW_MOD_ALT)
        {
            std::cout << "Alt ";
            mod_pressed = true;
        }
        if(mods & GLFW_MOD_SUPER)
        {
            std::cout << "Super ";
            mod_pressed = true;
        }
        if(mods & GLFW_MOD_CAPS_LOCK)
        {
            std::cout << "CapsLock ";
            mod_pressed = true;
        }
        if(mods & GLFW_MOD_NUM_LOCK)
        {
            std::cout << "NumLock ";
            mod_pressed = true;
        }
        if(mods & GLFW_MOD_SHIFT)
        {
            std::cout << "Shift ";
            mod_pressed = true;
        }
        else if(!mod_pressed)
            std::cout << "NONE ";
    }
}

#endif
