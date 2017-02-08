#ifndef NCURSES_APPLICATION_BINDINGS_H_
#define NCURSES_APPLICATION_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Widget.hpp"
#include "ncf/Component.hpp"
#include "common/Arguments.hpp"

#include <curses.h>
#include <cassert>
#include <vector>

struct Colors {
    colorPair colorPair1;
    colorPair colorPair2;
    colorPair colorPair3;
    colorPair colorPair4;
    colorPair colorPair5;
    colorPair colorPair6;
};

struct Attributes {
    short cursorVisibility;
    Colors colors;
};

class Application {
    public:
        /**
         * Application Constructor
         *
         * @param enableColors enables use of colors
         */
        explicit Application(bool enableColors = true);

        /**
         * Application Constructor
         *
         * @param args         command line arguments
         * @param enableColors enables use of colors
         */
        Application(Arguments args, bool enableColors = true);

        /**
         * Application Destructor
         */
        virtual ~Application();

        /**
         * Start the Application
         */
        virtual void start();

        inline void setInitialContext(Widget* widget)
        {
            assert(widget != NULL);
            m_currWdgtWithFocus = widget;
        }

        void setKillKey(char key)
        {
            //TODO: Check for key binding conflicts
            m_killKey = key;
        }

        char killKey()
        {
            return m_killKey;
        }

        /**
         * Attributes to use for menu and forms foregrounds
         *
         * @return default foreground attributes
         */
        virtual ncCharType foregrounds() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(1)) : A_BOLD;
        }

        /**
         * Attributes to use for menu and forms backgrounds
         *
         * @return default background attributes
         */
        virtual ncCharType backgrounds() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(2)) : A_NORMAL;
        }

        /**
         * Attributes to use for inactive (menu) elements
         *
         * @return default inactive attributes
         */
        virtual ncCharType inactives() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(3)|A_DIM) : A_DIM;
        }

        /**
         * Attributes to use for (form) labels and SLKs
         *
         * @return default label attributes
         */
        virtual ncCharType labels() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(4)) : A_NORMAL;
        }

        /**
         * Attributes to use for form backgrounds
         *
         * @return default form backgrounds
         */
        virtual ncCharType dialogBackgrounds() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(4)) : A_NORMAL;
        }

        /**
         * Attributes to use as default for (form) window backgrounds
         *
         * @return default window backgrounds
         */
        virtual ncCharType windowBackgrounds() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(5)) : A_NORMAL;
        }

        /**
         * Attributes to use for the title window
         *
         * @return default title window attributes
         */
        virtual ncCharType screenTitles() const {
            return m_hasColors ? static_cast<ncCharType>(COLOR_PAIR(6)) : A_BOLD;
        }

        /**
         * Get the Application instance
         *
         * @return the application instance
         */
        static Application* getApplication();

    private:
        /**
         * The unique Application instance
         */
        static Application* m_instance;

        /**
         * Window object for ncurses stdscr
         */
        Window* m_rootWindow = new Window(::stdscr);

        Widget* m_currWdgtWithFocus = nullptr;
        bool m_hasColors = true;
        char m_killKey = 'q';
};

#endif
