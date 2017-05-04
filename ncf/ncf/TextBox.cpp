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
  if (not hasWindow()) {
    if (not window) {
      window = make_unique<Panel>(getGeometry());
    }
    Widget::setWindow(std::move(window));
  }

  if (not hasSubWindow()) {
    if (not window) {
      subWindow = make_unique<Panel>(getWindow(),
          getWindow().height()-2, getWindow().width()-2, 1, 1, false
          );
    }
    Widget::setSubWindow(std::move(subWindow));
  }

  if (not m_pad) {
    m_pad = make_unique<Pad>(getWindow().height(), getWindow().width());
    m_pad->setWindow(&getWindow());
    m_pad->setSubWindow(&getSubWindow());
  }

  if (!m_content.empty()) {
    getSubWindow().clear();
    getSubWindow().writeString(m_content);
  }
}

void TextBox::setText(const string& text)
{
    m_content = text;
}

} // namespace ncf
