#include "ncf/TextView.hpp"

using namespace std;

namespace ncf {

TextView::TextView()
{
}

TextView::TextView(const Rect& rect) :
    View { rect }
{
}

void TextView::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    View::draw(std::move(window), std::move(subWindow));
}

int TextView::onKeyEvent(int ch)
{
    switch (ch) {
        case KEY_UP:break;
    }
    return 0;
}

void TextView::onMouseEvent(int ch)
{
    (void)ch;
}

bool TextView::onEvent(int ch)
{
    (void)ch;
    return false;
}

}
