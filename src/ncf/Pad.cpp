#include "ncf/Pad.hpp"
#include "ncf/NCException.hpp"
#include <cassert>

using namespace std;

namespace ncf {

Pad::Pad(int height, int width) :
    Window()
{
    m_window = ::newpad(height, width);
    if (static_cast<WINDOW*>(0) == m_window) {
        throw NCException("Cannot construct window");
    }
}

void Pad::refresh()
{
    noutrefresh();
    if (m_viewWin) {
        m_viewWin->refresh();
    }
}

void Pad::noutrefresh()
{
    Window* window = win();
    if (window) {
        int high = window->maxY();
        int wide = window->maxX();
        copy(*window, m_minRow, m_minCol,
                0, 0, high, wide,
                FALSE);
        window->syncUp();
        m_viewWin->noutrefresh();
    }
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

}
