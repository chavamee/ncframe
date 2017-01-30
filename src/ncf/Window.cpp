#include "ncf/Window.hpp"
#include "ncf/NCWindowException.hpp"
//TODO: Destructors

using namespace std;

bool Window::s_isInitialized = false;

Window::Window()
{
    if (!s_isInitialized) {
	    ::initscr();
	    s_isInitialized = true;
        /*if (colorInitialized == COLORS_NEED_INITIALIZATION) {
            colorInitialized = COLORS_NOT_INITIALIZED;
            useColors();
        }*/
        ::noecho();
        ::cbreak();
    }
}

Window::Window(WINDOW* win) :
    Window()
{
    m_handle = win ? win : ::stdscr;
    m_panel = ::new_panel(m_handle);
}

Window::Window(int height, int width, int y, int x) :
    Window()
{
    m_handle = ::newwin(height, width, y, x);
    if (m_handle == NULL) {
        throw NCException {"Could not create window"};
    }

    m_panel = ::new_panel(m_handle);
    if (m_panel == NULL) {
        throw NCException {"window error"};
    }
}

Window::Window(const Rect& rect) :
    Window(rect.size.height, rect.size.width, rect.origin.y, rect.origin.x)
{
}

Window::Window(Window& parent, int height, int width, int y, int x, bool derived) :
    Window()
{
    if (derived) {
        y -= parent.originY();
        x -= parent.originX();
    }

    m_handle = ::derwin(parent.getHandle(), height, width, y, x);
    if (m_handle == NULL) {
        throw NCException("window error");
    }

    m_panel = ::new_panel(m_handle);
    if (m_panel == NULL) {
        throw NCException("window error");
    }

    m_parent = &parent;
    m_sib = parent.m_subWins;
    parent.m_subWins = this;
}

Window::Window(Window&& rhs) :
    m_handle(rhs.m_handle),
    m_parent(rhs.m_parent),
    m_subWins(rhs.m_subWins),
    m_sib(rhs.m_sib)
{
    rhs.m_handle = NULL;
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

    if (m_handle != NULL) {
        ::delwin(m_handle);
    }
}

Window& Window::operator=(Window&& rhs)
{
    this->m_handle = rhs.m_handle;
    rhs.m_handle = NULL;
    return *this;
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

Size Window::size() const
{
    Size size {};
    getmaxyx(m_handle, size.height, size.width);
    return size;
}

string Window::getline(int n)
{
    char* cstr = nullptr;
    wgetnstr(m_handle, cstr, n);
    return string {cstr};
}

string Window::getlineFromPos(const Point& point, int n)
{
    char* cstr = nullptr;
    ::mvwgetnstr(m_handle, point.y, point.x, cstr, n);
    return string {cstr};
}

string Window::extractString(int n)
{
    char* cstr = nullptr;
    winnstr(m_handle, cstr, n);
    return string {cstr};
}

string Window::extractStringFromPos(const Point& point, int n)
{
    char* cstr = nullptr;
    ::mvwinnstr(m_handle, point.y, point.x, cstr, n);
    return string {cstr};
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

void Window::move(const Point& point)
{
    _onError( ::move_panel(m_panel, point.x, point.y) );
}

void Window::setPalette(const colorPair& color, colorPairID pair)
{
    _onError ( ::init_pair(pair, color.first, color.second) );
}

void Window::setPalette(colorPair color)
{
    setPalette(color, getPair());
}

void Window::setColor(colorPairID pair)
{

    if ((pair < 1) || (pair > COLOR_PAIRS)) {
        throw NCException("Can't set color pair");
    }

    attroff(A_COLOR);
    attrset(COLOR_PAIR(pair));
}

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

void Window::centerText(int y, const std::string& label)
{
    if (not label.empty()) {
        int x = (maxX() - label.size()) / 2;
        if (x<0) {
            x=0;
        }
        writeStringAtPos({y, x}, label.c_str());
    }
}

void Window::label(const std::string& topLabel, const std::string& bottomLabel)
{
    if (not topLabel.empty()) {
        centerText(0, topLabel);
    }
    if (not bottomLabel.empty()) {
        centerText(maxY(), bottomLabel);
    }
}

void Window::frame(const std::string& title,const std::string& btitle)
{
    box();
    if (not title.empty() && not btitle.empty()) {
        label(title, btitle);
    }
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

void Window::redrawAll()
{
    PANEL *pan;

    pan = ::panel_above(NULL);
    while (pan) {
        ::touchwin(panel_window(pan));
        pan = ::panel_above(pan);
    }
    ::update_panels();
    ::doupdate();
}
