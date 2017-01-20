#include "ncf/Pad.hpp"
#include "ncf/NCException.hpp"
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

int Pad::refresh()
{
    int res = noutrefresh();
    if (res==OK && (m_viewWin)) {
        res = (m_viewWin->refresh());
    }

    return res;
}

int Pad::noutrefresh()
{
    int res = OK;
    Window* window = win();
    if (window) {
        int high = window->maxY();
        int wide = window->maxX();
        res = copy(*window, m_minRow, m_minCol,
                0, 0, high, wide,
                FALSE);
        if (res==OK) {
            window->syncUp();
            res = m_viewWin->noutrefresh();
        }
    }

    return res;
}

void Pad::setWindow(Window* view,
        int v_grid,
        int h_grid
        )
{
    m_viewWin = view;
    m_minRow = m_minCol = 0;
    if (h_grid <=0 || v_grid <= 0) {
        NCException("Illegal Gridsize");
    } else {
        m_horizGridsize = h_grid;
        m_vertGridsize = v_grid;
    }
}

void Pad::setSubWindow(Window* sub)
{
    if (!m_viewWin) {
        NCException("Pad has no viewport");
    }

    assert(m_viewWin != nullptr);
    if (!m_viewWin->isDescendant(*sub)) {
        NCException("NCursesFramePad"/*, E_SYSTEM_ERROR*/);
    }

    m_viewSub = sub;
}
