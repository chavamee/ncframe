#ifndef NCURSES_APPLICATION_BINDINGS_H_
#define NCURSES_APPLICATION_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Widget.hpp"
#include "ncf/Component.hpp"
#include "common/Arguments.hpp"

#include <curses.h>
#include <cassert>
#include <vector>

//TODO: Create a pointer/unique_ptr/object to stdscr window that is const and unmovable.

namespace ncf {

struct Colors {
    ColorPair ColorPair1;
    ColorPair ColorPair2;
    ColorPair ColorPair3;
    ColorPair ColorPair4;
    ColorPair ColorPair5;
    ColorPair ColorPair6;
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

        //void setController(std::unique_ptr<Controller> controller);

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
        virtual NCCharType foregrounds() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(1)) : A_BOLD;
        }

        /**
         * Attributes to use for menu and forms backgrounds
         *
         * @return default background attributes
         */
        virtual NCCharType backgrounds() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(2)) : A_NORMAL;
        }

        /**
         * Attributes to use for inactive (menu) elements
         *
         * @return default inactive attributes
         */
        virtual NCCharType inactives() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(3)|A_DIM) : A_DIM;
        }

        /**
         * Attributes to use for (form) labels and SLKs
         *
         * @return default label attributes
         */
        virtual NCCharType labels() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(4)) : A_NORMAL;
        }

        /**
         * Attributes to use for form backgrounds
         *
         * @return default form backgrounds
         */
        virtual NCCharType dialogBackgrounds() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(4)) : A_NORMAL;
        }

        /**
         * Attributes to use as default for (form) window backgrounds
         *
         * @return default window backgrounds
         */
        virtual NCCharType windowBackgrounds() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(5)) : A_NORMAL;
        }

        /**
         * Attributes to use for the title window
         *
         * @return default title window attributes
         */
        virtual NCCharType screenTitles() const {
            return m_hasColors ? static_cast<NCCharType>(COLOR_PAIR(6)) : A_BOLD;
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

        Widget* m_currWdgtWithFocus = nullptr;
        bool m_hasColors = true;
        char m_killKey = 'q';
};

}
#endif
