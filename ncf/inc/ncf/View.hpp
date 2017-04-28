#ifndef NCF_VIEW_H
#define NCF_VIEW_H

#include "ncf/Widget.hpp"
#include "ncf/Pad.hpp"

//TODO: Turn into model/view

namespace ncf {

class View : public Widget {
    public:
        View()
        {
        }

        View(const Rect& rect);

        virtual ~View()
        {
        }

        void setContent(const std::string& content)
        {
            m_content = content;
            if (getSubWindow()) {
                getSubWindow()->clear();
                getSubWindow()->writeString(m_content);
            }
        }

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

    private:
        std::unique_ptr<Pad> m_pad;
        std::string m_content;
};

}

#endif
