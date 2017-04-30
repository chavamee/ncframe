#include <ncf/TextBox.hpp>
#include <ncf/Panel.hpp>

using namespace std;

namespace ncf {

TextBox::TextBox() :
    Widget {}
{
}

TextBox::TextBox(const Rect& rect) :
    Widget {rect}
{
}

TextBox::~TextBox()
{
}

int TextBox::onKeyEvent(int ch)
{
    switch (ch) {
        case KEY_UP:break;
    }
    return 0;
}

void TextBox::onMouseEvent(int ch)
{
    (void)ch;
}

bool TextBox::onEvent(int ch)
{
    (void)ch;
    return false;
}

void TextBox::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (!window) {
        if (getWindow()) {
            // TODO: Use this window
        } else {
            //TODO: Make default window
            window = make_unique<Panel>(getGeometry());
        }
    }

    if (!subWindow) {
        subWindow = make_unique<Panel>(
                *window, window->height()-2, window->width()-2, 1, 1, false
                );
        m_pad = make_unique<Pad>(window->height(), window->width());

        m_pad->setWindow(window.get());
        m_pad->setSubWindow(subWindow.get());

        if (!m_content.empty()) {
            subWindow->writeString(m_content);
        }

        Widget::setWindow(std::move(window));
        Widget::setSubWindow(std::move(subWindow));
    }
}

void TextBox::setText(const string& text)
{
    m_content = text;
    if (getSubWindow()) {
        getSubWindow()->clear();
        getSubWindow()->writeString(m_content);
    }
}

} // namespace ncf
