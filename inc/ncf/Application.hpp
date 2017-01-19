#ifndef NCURSES_APPLICATION_BINDINGS_H_
#define NCURSES_APPLICATION_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Widgets.hpp"
#include "ncf/Component.hpp"
#include <curses.h>
#include <cassert>
#include <vector>

using ColorPair = std::pair<int, int>;

struct Colors {
    ColorPair colorPair1;
    ColorPair colorPair2;
    ColorPair colorPair3;
    ColorPair colorPair4;
    ColorPair colorPair5;
    ColorPair colorPair6;
};

struct Attributes {
    short cursorVisibility;
    Colors colors;
};

class Application {
    public:
        Application();
        Application(bool enableColors);
        Application(int argc, char *argv[], bool enableColors = true);
        virtual ~Application();
        virtual void Start();

        void initializeNCurses();

        inline void SetInitialContext(Widget* widget)
        {
            assert(widget != NULL);
            m_currWdgtWithFocus = widget;
        }

        void SetKillKey(char key)
        {
            //TODO: Check for key binding conflicts
            m_killKey = key;
        }

        char KillKey()
        {
            return m_killKey;
        }

    private:
        Window* m_rootWindow = new Window(::stdscr);
        Widget* m_currWdgtWithFocus = nullptr;
        bool m_enableColors = true;
        char m_killKey = 'q';
};

#endif
