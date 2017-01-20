#include "ncf/Window.hpp"
#include "ncf/NCException.hpp"
//TODO: Destructors

Window::Window()
{
}

Window::Window(WINDOW* win) :
    Window()
{
    m_handle = win ? win : ::stdscr;
    m_panel = ::new_panel(m_handle);
}

Window::Window(int height, int width, int y, int x)
{
    m_handle = newwin(height, width, y, x);
    if (m_handle == NULL) {
        throw NCException("Could not create window");
    }

    m_panel = ::new_panel(m_handle);
    if (m_panel == NULL) {
        throw NCException("window error");
    }
}

Window::Window(const Rect& rect) :
    Window(rect.size.height, rect.size.width, rect.origin.y, rect.origin.x)
{
}

Window::Window(Window& parent, int height, int width, int y, int x, bool derived) :
    m_parent(&parent),
    m_sib(parent.m_subWins)
{
    if (derived) {
        y -= parent.originY();
        x -= parent.originX();
    }

    m_handle = derwin(parent.getHandle(), height, width, y, x);
    if (m_handle == NULL) {
        throw NCException("window error");
    }

    m_panel = ::new_panel(m_handle);
    if (m_panel == NULL) {
        throw NCException("window error");
    }
    parent.m_subWins = this;
}

void Window::printStr(const std::string& str)
{
    waddnstr(m_handle, str.c_str(), str.size());
}

Window::~Window()
{
    _killSubwindows();

    if (m_parent) {
        // Remove this window from the parent's list of subwindows.
        Window* next = m_parent->m_subWins;
        Window* prev = 0;
        while (next != 0) {
            if (next == this) {
                if (prev != 0) {
                    prev->m_sib = next->m_sib;
                } else {
                    m_parent->m_subWins = next->m_sib;
                }
                break;
            }
            prev = next;
            next = next->m_sib;
        }
    }

    if (/*alloced &&*/ m_handle != NULL) {
        ::delwin(m_handle);
    }

}

Point Window::getCursorPosition() const
{
    Point pt;
    getyx(m_handle, pt.y, pt.x);
    return pt;
}

Point Window::getOriginPoint() const
{
    Point pt;
    getbegyx(m_handle, pt.y, pt.x);
    return pt;
}

int Window::size() const
{
    int x = 0;
    int y = 0;
    getmaxyx(m_handle, y, x);
    return x * y;
}

int Window::getline(std::string& str, int n)
{
    char* cstr = nullptr;
    int count = wgetnstr(m_handle, cstr, n);
    str = cstr;
    return count;
}

int Window::getlineFromPos(int y, int x, std::string& str, int n)
{
    char* cstr = nullptr;
    int count = mvwgetnstr(m_handle, y, x, cstr, n);
    str = cstr;
    return count;
}

int Window::extractString(std::string& str, int n)
{
    char* cstr = nullptr;
    int count = winnstr(m_handle, cstr, n);
    str = cstr;
    return count;
}

int Window::extractStringFromPos(int y, int x, std::string& str, int n)
{
    char* cstr = nullptr;
    int count = mvwinnstr(m_handle, y, x, cstr, n);
    str = cstr;
    return count;
}

int Window::getStrAtPos(int y, int x, chtype* str, int n)
{
    chtype* cstr = nullptr;
    int count = mvwinchnstr(m_handle, y, x, cstr, n);
    str = cstr;
    return count;
}

short Window::getPair() const
{
    return static_cast<short>(PAIR_NUMBER(getattrs(m_handle)));
}

void Window::top()
{
    ::top_panel(m_panel);
}

void Window::hide()
{
    ::hide_panel(m_panel);
}

void Window::show()
{
    ::show_panel(m_panel);
}

void Window::move(int x, int y)
{
    ::move_panel(m_panel, x, y);
}

int Window::setPalette(short fore, short back, short pair)
{
    return ::init_pair(pair, fore, back);
}

int Window::setPalette(short fore, short back)
{
    return setPalette(fore, back, getPair());
}

/*int Window::setColor(short pair)
{
	if ((pair < 1) || (pair > COLOR_PAIRS)) {
	    return -1;
    }

	attroff(A_COLOR);
	attrset(COLOR_PAIR(pair));
    return OK;
}*/

bool Window::isDescendant(Window& win)
{
    bool result = false;

    for (Window* p = m_subWins; p != NULL; p = p->m_sib) {
	if (p == &win || p->isDescendant(win)) {
	    result = TRUE;
	    break;
	}
    }
    return result;
}

void Window::_killSubwindows()
{
    Window* p = m_subWins;

    m_subWins = nullptr;
    while (p != nullptr) {
        Window* q = p->m_sib;
        p->_killSubwindows();
        //if (p->alloced) {
            if (p->getHandle())
                ::delwin(p->getHandle());
        //}
        delete p;
        p = q;
    }
}
