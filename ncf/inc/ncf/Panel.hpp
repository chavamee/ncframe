#ifndef NCF_NCURSES_PANEL_H
#define NCF_NCURSES_PANEL_H

#include <cursesw.h>
extern "C" {
#  include <panel.h>
}

#include "Window.hpp"

namespace ncf {

class Panel : public Window {
    public:
        /**
         * Default panel constructor
         */
        Panel();

        /**
         * Construct a Panel with the given dimensions
         *
         * @param height panel height
         * @param width  panel width
         * @param y      panel y position
         * @param x      panel x position
         */
        Panel(int height, int width, int y = 0, int x = 0);

        /**
         * Construct a Panel with the given geometry
         *
         * @param rect panel rectangular geometry
         */
        Panel(const Rect& rect);

        Panel(Window& parent,
              int height,
              int width,
              int y = 0,
              int x = 0,
              bool derived = false
              );

        /**
         * Copying is not allowed.
         *
         * Use clone instead.
         */
        Panel& operator=(const Panel& rhs) = delete;

        /**
         * Copying is not allowed.
         *
         * Use clone instead.
         */
        Panel(const Panel& rhs) = delete;

        /**
         * Destructor
         */
        virtual ~Panel();

        /**
         * Make this panel the top panel in the stack.
         */
        void top();

        /**
         * Make this panel the bottom panel in the stack.
         *
         * NOTE: The panel associated with ::stdscr is always on the bottom. So
         * actually bottom() makes the panel the first above ::stdscr.
         */
        void bottom();

        /**
         * Show the panel, i.e. make it visible.
         */
        void show();

        /**
         * Hide the panel.
         *
         * Theh panel will stays in the stack but becomes invisible.
         */
        void hide();

        /**
         * Check if the panel is hidden.
         *
         * @return true if the panel is hidden, false otherwise.
         */
        bool isHidden()
        {
            return ::panel_hidden(m_panel);
        }

        /**
         * Move the panel.
         *
         * @param pos move the panel origin to the given position
         */
        void move(const Point& pos);

        /**
         * Propagate all panel changes to the virtual screen and update the
         * physical screen.
         */
        void refresh() override;

        /**
         * Propagate all panel changes to the virtual screen.
         */
        void noutrefresh() override;

        /**
         * Refresh all existing panels
         */
        static void redrawAll();

    private:
        static void _onError(int err);

        /**
         * NCurses PANEL handle
         */
        PANEL* m_panel = nullptr;

};

} // namespace ncf

#endif
