#include "ncurses/View.hpp"
#include "ncurses/NCException.hpp"
#include <cassert>

using namespace std;

Pad::Pad(int height, int width) :
    Window()
{
    m_handle = ::newpad(height, width);
    if (static_cast<WINDOW*>(0) == m_handle) {
        throw NCException("Cannot construct window");
    }
}

int Pad::Refresh()
{
    int res = NoutRefresh();
    if (res==OK && (m_viewWin)) {
        res = (m_viewWin->Refresh());
    }

    return res;
}

int Pad::NoutRefresh()
{
    int res = OK;
    Window* win = Win();
    if (win) {
        int high = win->MaxY();
        int wide = win->MaxX();
        res = Copy(*win, m_minRow, m_minCol,
                0, 0, high, wide,
                FALSE);
        if (res==OK) {
            win->SyncUp();
            res = m_viewWin->NoutRefresh();
        }
    }

    return res;
}

void Pad::SetWindow(unique_ptr<Window> view,
        int v_grid,
        int h_grid
        )
{
    m_viewWin = std::move(view);
    m_minRow = m_minCol = 0;
    if (h_grid <=0 || v_grid <= 0) {
        NCException("Illegal Gridsize");
    } else {
        m_horizGridsize = h_grid;
        m_vertGridsize = v_grid;
    }
}

void Pad::SetSubWindow(unique_ptr<Window> sub)
{
    if (!m_viewWin) {
        NCException("Pad has no viewport");
    }

    assert(m_viewWin != nullptr);
    if (!m_viewWin->isDescendant(*sub)) {
        NCException("NCursesFramePad"/*, E_SYSTEM_ERROR*/);
    }

    m_viewSub = std::move(sub);
}

View::View(int height, int width) :
    Widget{ height, width }
{
}

void ScrollableView::Draw(unique_ptr<Window>& window)
{
    if (window) {
        if (GetWindow()) {
            // TODO: Use this window
        } else {
            //TODO: Make default window
        }
    }

    m_pad = make_unique<Pad>(new Pad(Height(), Width()));
    m_pad->SetSubWindow(GetSubWindow());
}
