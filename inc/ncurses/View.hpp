#ifndef NCURSES_VIEW_HPP_
#include "ncurses/Widgets.hpp"

class Pad;

// TODO: ScrollableView and View should own the window not Widget
//       ScrollableView will own a pad
//       View will own a Window

class View : public Widget {
    public:
        View()
        {
        }
        View(int height, int width);
};

class ScrollableView : public View {
    public:
        ScrollableView()
        {
        }

        ScrollableView(int height, int width);

    private:
        std::unique_ptr<Pad> m_pad;
};


// -------------------------------------------------------------------------
// Pad Support. We allow an association of a pad with a "real" window
// through which the pad may be viewed.
// -------------------------------------------------------------------------
class Pad : public Window {
    private:
        std::unique_ptr<Window> m_viewWin = {};       // the "viewport" window
        std::unique_ptr<Window> m_viewSub = {};       // the "viewport" subwindow
        int m_horizGridsize = 0;
        int m_vertGridsize  = 0;

    protected:
        int m_minRow = 0;
        int m_minCol = 0;         // top left row/col of the pads display area

        Window* Win(void) const {
            // Get the window into which the pad should be copied (if any)
            return m_viewSub ? m_viewSub.get() : (m_viewWin.get() ? m_viewWin.get() : nullptr);
        }

        Window& GetWindow(void) const {
            return *m_viewWin.get();
        }

        Window& GetSubWindow(void) const {
            return *m_viewSub.get();
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

    public:
        Pad(int nlines, int ncols);
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
            m_horizGridsize(rhs.m_horizGridsize),
            m_vertGridsize(rhs.m_vertGridsize),
            m_minRow(rhs.m_minRow),
            m_minCol(rhs.m_minCol)
    {
    }

        virtual ~Pad() {}

        int echochar(const chtype ch) { return ::pechochar(m_handle, ch); }
        // Put the attributed character onto the pad and immediately do a
        // prefresh().

        int Refresh();
        // If a viewport is defined the pad is displayed in this window, otherwise
        // this is a noop.

        int Refresh(int pminrow, int pmincol,
                int sminrow, int smincol,
                int smaxrow, int smaxcol) {
            return ::prefresh(m_handle, pminrow, pmincol,
                    sminrow, smincol, smaxrow, smaxcol);
        }
        // The coordinates sminrow,smincol,smaxrow,smaxcol describe a rectangle
        // on the screen. <b>refresh</b> copies a rectangle of this size beginning
        // with top left corner pminrow,pmincol onto the screen and calls doupdate().

        int NoutRefresh();
        // If a viewport is defined the pad is displayed in this window, otherwise
        // this is a noop.

        int RoutRefresh(int pminrow, int pmincol,
                int sminrow, int smincol,
                int smaxrow, int smaxcol) {
            return ::pnoutrefresh(m_handle, pminrow, pmincol,
                    sminrow, smincol, smaxrow, smaxcol);
        }
        // Does the same as refresh() but without calling doupdate().

        virtual void SetWindow(std::unique_ptr<Window> view, int v_grid = 1, int h_grid = 1);
        // Add the window "view" as viewing window to the pad.

        virtual void SetSubWindow(std::unique_ptr<Window> sub);
        // Use the subwindow "sub" of the viewport window for the actual viewing.
        // The full viewport window is usually used to provide some decorations
        // like frames, titles etc.
};

#endif
