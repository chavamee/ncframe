#ifndef NCF_NCURSES_PAD_H
#define NCF_NCURSES_PAD_H

#include "ncf/ncurses/Window.hpp"

namespace ncf {
namespace ncurses {

// -------------------------------------------------------------------------
// Pad Support. We allow an association of a pad with a "real" window
// through which the pad may be viewed.
// -------------------------------------------------------------------------
class Pad : public Window {
    public:
        Pad(int height, int width);
        // create a pad with the given size

        Pad& operator=(const Pad& rhs)
        {
            if (this != &rhs) {
                *this = rhs;
            }
            return *this;
        }

        Pad(const Pad& rhs) :
            //TODO
            //m_viewWin(rhs.m_viewWin),
            //m_viewSub(rhs.m_viewSub),
            m_minRow(rhs.m_minRow),
            m_minCol(rhs.m_minCol),
            m_horizGridsize(rhs.m_horizGridsize),
            m_vertGridsize(rhs.m_vertGridsize)
        {
        }

        virtual ~Pad() {}

        int echochar(const chtype ch) { return ::pechochar(m_window, ch); }
        // Put the attributed character onto the pad and immediately do a
        // prefresh().

        void refresh();
        // If a viewport is defined the pad is displayed in this window, otherwise
        // this is a noop.

        int refresh(int pminrow, int pmincol,
                int sminrow, int smincol,
                int smaxrow, int smaxcol) {
            return ::prefresh(m_window, pminrow, pmincol,
                    sminrow, smincol, smaxrow, smaxcol);
        }
        // The coordinates sminrow,smincol,smaxrow,smaxcol describe a rectangle
        // on the screen. <b>refresh</b> copies a rectangle of this size beginning
        // with top left corner pminrow,pmincol onto the screen and calls doupdate().

        void noutrefresh();
        // If a viewport is defined the pad is displayed in this window, otherwise
        // this is a noop.

        void routrefresh(int pminrow, int pmincol,
                int sminrow, int smincol,
                int smaxrow, int smaxcol) {
            _onError ( ::pnoutrefresh(m_window, pminrow, pmincol,
                    sminrow, smincol, smaxrow, smaxcol) );
        }
        // Does the same as refresh() but without calling doupdate().

        void setWindow(Window* view, int v_grid = 1, int h_grid = 1);
        // Add the window "view" as viewing window to the pad.

        void setSubWindow(Window* sub);
        // Use the subwindow "sub" of the viewport window for the actual viewing.
        // The full viewport window is usually used to provide some decorations
        // like frames, titles etc.

    protected:
        int m_minRow = 0;
        int m_minCol = 0;         // top left row/col of the pads display area

        Window* win(void) const {
            // Get the window into which the pad should be copied (if any)
            return m_viewSub ? m_viewSub : (m_viewWin ? m_viewWin : nullptr);
        }

        Window& getWindow(void) const {
            return *m_viewWin;
        }

        Window& getSubWindow(void) const {
            return *m_viewSub;
        }

        /*TODO: virtual int driver (int key);      // Virtualize keystroke key
        // The driver translates the keystroke c into an Pad_Request

        virtual void OnUnknownOperation(int pad_req) {
        (void) pad_req;
        ::beep();
        }
        // This is called if the driver returns an unknown op-code

        virtual void OnNavigationError(int pad_req) {
        (void) pad_req;
        ::beep();
        }
        // This is called if a navigation request couldn't be satisfied

        virtual void OnOperation(int pad_req) {
        (void) pad_req;
        };
        // OnOperation is called if a Pad_Operation was executed and just before
        // the refresh() operation is done.*/

    private:
        Window* m_viewWin = nullptr;       // the "viewport" window*/
        Window* m_viewSub = nullptr;       // the "viewport" subwindow*/

        void _onError(int err);

        int m_horizGridsize = 0;
        int m_vertGridsize  = 0;

};

}
}
#endif
