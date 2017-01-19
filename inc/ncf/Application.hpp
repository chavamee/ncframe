#ifndef NCURSES_APPLICATION_BINDINGS_H_
#define NCURSES_APPLICATION_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Widgets.hpp"
#include "ncf/Component.hpp"
#include <curses.h>
#include <cassert>
#include <vector>

//TODO: Should probably be a singleton

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

        // Attributes to use for menu and forms foregrounds
        virtual chtype Foregrounds() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(1)) : A_BOLD;
        }

        // Attributes to use for menu and forms backgrounds
        virtual chtype Backgrounds() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(2)) : A_NORMAL;
        }

        // Attributes to use for inactive (menu) elements
        virtual chtype Inactives() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(3)|A_DIM) : A_DIM;
        }

        // Attributes to use for (form) labels and SLKs
        virtual chtype Labels() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(4)) : A_NORMAL;
        }

        // Attributes to use for form backgrounds
        virtual chtype DialogBackgrounds() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(4)) : A_NORMAL;
        }

        // Attributes to use as default for (form) window backgrounds
        virtual chtype window_backgrounds() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(5)) : A_NORMAL;
        }

        // Attributes to use for the title window
        virtual chtype screen_titles() const {
            return m_hasColors ? static_cast<chtype>(COLOR_PAIR(6)) : A_BOLD;
        }


        static Application* GetApplication();

        static Application* m_instance;

    private:
        Window* m_rootWindow = new Window(::stdscr);
        Widget* m_currWdgtWithFocus = nullptr;
        bool m_hasColors = true;
        char m_killKey = 'q';
};

#endif
