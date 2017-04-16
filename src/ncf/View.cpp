#include "ncf/View.hpp"
#include "ncf/NCException.hpp"

using namespace std;

namespace ncf {

View::View(const Rect& rect) :
    Widget{ rect }
{
}

void View::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (!window) {
        if (getWindow()) {
            // TODO: Use this window
        } else {
            //TODO: Make default window
            window = make_unique<Window>(getGeometry());
        }
    }

    if (!subWindow) {
        subWindow = make_unique<Window>(
                *window, window->height()-2, window->width()-2, 1, 1, false
                );
        m_pad = make_unique<Pad>(window->height(), window->width());

        m_pad->setWindow(window.get());
        m_pad->setSubWindow(subWindow.get());

        if (!m_content.empty()) {
            subWindow->writeString(m_content);
        }

        setWindow(std::move(window));
        setSubWindow(std::move(subWindow));

    }

}

}
