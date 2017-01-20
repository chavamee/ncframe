#ifndef NCURSES_VIEW_HPP_

#include "ncf/Widget.hpp"
#include "ncf/Pad.hpp"

// TODO: ScrollableView and View should own the window not Widget
//       ScrollableView will own a pad
//       View will own a Window

//TODO: Turn into model/view

class View : public Widget {
    public:
        View()
        {
        }

        View(const Rect& rect);

        void setContent(const std::string& content)
        {
            m_content = content;
            if (getSubWindow()) {
                getSubWindow()->clear();
                getSubWindow()->printStr(m_content);
            }
        }

        virtual ~View()
        {
        }


        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

    private:
        std::unique_ptr<Pad> m_pad;
        std::string m_content;
};

#endif
