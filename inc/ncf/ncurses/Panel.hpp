#ifndef NCF_NCURSES_PANEL_H
#define NCF_NCURSES_PANEL_H


#include <cursesw.h>
extern "C" {
#  include <panel.h>
}

#include "Window.hpp"

namespace ncf {
namespace ncurses {

class Panel : public Window {
    public:
        Panel();

        Panel(int height, int width, int y = 0, int x = 0);

        Panel& operator=(const Panel& rhs);

        Panel(const Panel& rhs) = delete;

        virtual ~Panel();

        /**
         * Make this window the top window in the stack.
         */
        void top();

        /**
         * Make this window the bottom window in the stack.
         *
         * N.B.: The panel associated with ::stdscr is always on the bottom. So
         * actually bottom() makes the panel the first above ::stdscr.
         */
        void bottom();

        /**
         * Show the window, i.e. make it visible.
         */
        void show();

        /**
         * Hide the window.
         *
         * It stays in the stack but becomes invisible.
         */
        void hide();

        /**
         * Check if the window is hidden.
         *
         * @return true if the panel is hidden, false otherwise.
         */
        bool isHidden()
        {
            return ::panel_hidden(m_panel);
        }

        /**
         * Move the window.
         *
         * @param point move the window origin to the given point
         */
        void move(const Point& point);

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

        /**
         * Put a frame around the panel and put the title centered in the top line
         * and a bottom title in the bottom line.
         *
         * @param title      top title
         * @param btmm_title bottom title
         */
        virtual void frame(const std::string& title = "", const std::string& bttm_title = "");

        /* TODO
         * virtual void boldframe(const char* title=NULL,
                const char* btitle=NULL);
        // Same as frame(), but use highlighted attributes.
        */

        /**
         * Put the title centered in the top line and btitle in the bottom line.
         *
         * @param topLablel   top line title
         * @param bottomLabel bottom lien ttile
         *
         */
        virtual void label(const std::string& topLabel,
                const std::string& bottomLabel);

        /**
         * Put the label text centered in the specified row.
         *
         * @param y     the y position to center the text to
         * @param label the label to center
         */
        virtual void centerText(int y, const std::string& label);

    private:
        static void _onError(int err)
        {
        }

        /**
         * NCurses PANEL handle
         */
        PANEL* m_panel = nullptr;

};

} // namespace ncf
} // namespace ncurses

#endif
