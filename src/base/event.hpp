//author Ryan Bailey

#ifndef RYDE_BASE_EVENT_HPP
#define RYDE_BASE_EVENT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//the program should never have to deal with Events of type BASE, if it does encounter
//one, that's an error. Eventype::BASE only exists because there are base classes that
//the Event types are derived from. As those classes have a base type of Event, they
//technically could be used by the program. Though as mentioned above, they shouldn't
//be. If you do encounter an event of type BASE, that means that an event of type Event,
//MouseKeyBaseEvent, or CursorScrollBaseEvent, has been sent in error, as if it was a
//real event.

enum class EventType
{
    BASE,
    KEY,
    CHAR,
    MOUSE,
    CURSOR,
    SCROLL
};

class Event
{
protected:
    EventType type {EventType::BASE};
public:
    Event()=default;
    EventType get_type();
};

class MouseKeyBaseEvent : public Event
{
    int action, mods;
public:
    MouseKeyBaseEvent(int action, int mods);
    int get_action();
    int get_mods();
};

class CursorScrollBaseEvent : public Event
{
    double x, y;
public:
    CursorScrollBaseEvent(double x, double y);
    double get_x();
    double get_y();
};

class MouseEvent : public MouseKeyBaseEvent
{
    int button;
public:
    MouseEvent(int button, int action, int mods);
    int get_button();
};

class KeyEvent : public MouseKeyBaseEvent
{
    int key;
public:
    KeyEvent(int key, int action, int mods);
    int get_key();
};

class CursorEvent : public CursorScrollBaseEvent
{
public:
    CursorEvent(double x, double y);
};

class ScrollEvent : public CursorScrollBaseEvent
{
public:
    ScrollEvent(double x, double y);
};

class CharEvent : public Event
{
    unsigned int codepoint;
public:
    CharEvent(unsigned int codepoint);
    unsigned int get_codepoint();
};

//for debugging purposes
#ifndef NDEBUG
void print_event(Event* e);

namespace PrintEventFunctions //these are functions only used by print_event
{
    void print_action(int action);
    void print_mods(int mods);
}
#endif

#endif
