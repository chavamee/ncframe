#include "ncf/View.hpp"
#include "ncf/NCException.hpp"

using namespace std;

View::View(int height, int width) :
    Widget{ height, width }
{
}

void View::Draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (!window) {
        if (GetWindow()) {
            // TODO: Use this window
        } else {
            //TODO: Make default window
            window = make_unique<Window>(Height(), Width() /*, OriginX(), OriginY()*/);
        }
    }

    if (!subWindow) {
        subWindow = make_unique<Window>(
                *window, window->Height()-2, window->Width()-2, 1, 1, false
                );
    }

    m_pad = make_unique<Pad>(window->Height(), window->Width());

    SetWindow(std::move(window));
    SetSubWindow(std::move(subWindow));

    m_pad->SetWindow(GetWindow());
    m_pad->SetSubWindow(GetSubWindow());

    if (!m_content.empty()) {
        GetSubWindow()->PrintStr(m_content);
    }
}
