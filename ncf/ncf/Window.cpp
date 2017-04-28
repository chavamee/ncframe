#include "ncf/Window.hpp"
#include "ncf/NCWindowException.hpp"
//TODO: Destructors

using namespace std;

namespace ncf {

bool Window::s_isInitialized = false;

Window::Window()
{
    initialize();
}

Window::Window(WINDOW*& win, bool takeOnwership) :
    m_isHandleOwner(takeOnwership)
{
    initialize();
    m_window = win ? win : ::stdscr;
    if (takeOnwership && win != ::stdscr) {
        win = nullptr;
    }
}

Window::Window(int height, int width, int y, int x)
{
    initialize();
    m_window = ::newwin(height, width, y, x);
    if (m_window == nullptr) {
        throw NCException {"Could not create window"};
    }
}

Window::Window(const Rect& rect) :
    Window(rect.size.height, rect.size.width, rect.origin.y, rect.origin.x)
{
}

Window::Window(Window& parent, int height, int width, int y, int x, bool derived)
{
    if (derived) {
        y -= parent.originY();
        x -= parent.originX();
    }

    initialize();
    m_window = ::derwin(parent.getHandle(), height, width, y, x);
    if (m_window == nullptr) {
        throw NCException("window error");
    }

    m_parent = &parent;
    m_sib = parent.m_subWins;
    parent.m_subWins = this;
}
Window::Window(Window& parent, const Rect& rect, bool dervied) :
    Window(parent, rect.size.height, rect.size.width, rect.origin.y, rect.origin.x, dervied)
{
}

Window::Window(Window&& rhs) :
    m_window(rhs.m_window),
    m_parent(rhs.m_parent),
    m_subWins(rhs.m_subWins),
    m_sib(rhs.m_sib)
{
    rhs.m_window = nullptr;
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

    if (m_window != nullptr && m_isHandleOwner) {
        ::delwin(m_window);
    }
}

Window& Window::operator=(Window&& rhs)
{
    this->m_window = rhs.m_window;
    rhs.m_window = nullptr;
    return *this;
}

Point Window::getCursorPosition() const
{
    Point pt;
    getyx(m_window, pt.y, pt.x);
    return pt;
}

Point Window::getOrigin() const
{
    Point pt;
    getbegyx(m_window, pt.y, pt.x);
    return pt;
}

Size Window::size() const
{
    Size size {};
    getmaxyx(m_window, size.height, size.width);
    return size;
}

int Window::getKeystroke()
{
    int resp = wgetch(m_window);
    if (resp != ERR) {
        return resp;
    }

    _onError(ERR);
    return -1;
}

string Window::getline(int n)
{
    char* cstr = nullptr;
    _onError ( ::wgetnstr(m_window, cstr, n) );
    return string {cstr};
}

string Window::getlineFromPos(const Point& point, int n)
{
    char* cstr = nullptr;
    _onError ( mvwgetnstr(m_window, point.y, point.x, cstr, n) );
    return string {cstr};
}

string Window::extractString(int n)
{
    char* cstr = nullptr;
    _onError ( ::winnstr(m_window, cstr, n) );
    return string {cstr};
}

string Window::extractStringFromPos(const Point& point, int n)
{
    char* cstr = nullptr;
    _onError ( mvwinnstr(m_window, point.y, point.x, cstr, n) );
    return string {cstr};
}

short Window::getPair() const
{
    return static_cast<short>(PAIR_NUMBER(getattrs(m_window)));
}

void Window::setPalette(const ColorPair& Color, ColorPairID pair)
{
    _onError ( ::init_pair(pair, Color.first, Color.second) );
}

void Window::setPalette(ColorPair Color)
{
    setPalette(Color, getPair());
}

void Window::setColor(ColorPairID pair)
{

    if ((pair < 1) || (pair > COLOR_PAIRS)) {
        throw NCException("Can't set color pair");
    }

    attributeOff(A_COLOR);
    setAttribute(COLOR_PAIR(pair));
}

bool Window::isDescendant(Window& win)
{
    bool result = false;

    for (Window* p = m_subWins; p != nullptr; p = p->m_sib) {
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
        if (p->getHandle())
            ::delwin(p->getHandle());
        delete p;
        p = q;
    }
}

void Window::_onError(int err)
{
    if (err != E_OK) {
        throw NCWindowException("Window error", err);
    }
}

} // namespace ncf
