#ifndef NCF_TEXT_BOX_H
#define NCF_TEXT_BOX_H

#include <ncf/Widget.hpp>
#include <ncf/Pad.hpp>

namespace ncf {

class TextBox : public Widget {

public:
    TextBox();

    TextBox(const Rect& rect);

    virtual ~TextBox();

    void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

    int onKeyEvent(int ch) override;

    void onMouseEvent(int ch) override;

    bool onEvent(int ch) override;

    void setText(const std::string& text);

private:
    std::unique_ptr<Pad> m_pad;
    std::string m_content;
};

} // namespace ncf

#endif /* NCF_TEXT_BOX_H */
