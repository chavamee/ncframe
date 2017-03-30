#ifndef NCURSES_WIDGETS_H_
#define NCURSES_WIDGETS_H_

#include "ncf/Component.hpp"
#include "ncf/Geometry.hpp"

#include <algorithm>

namespace ncf {

//TODO: Check for inlinening opportunities

class Widget : public Component {
    public:
        Widget();

        Widget(const Rect& rect);

        virtual int onKeyEvent(int ch)
        {
            NCF_UNUSED(ch);
            return ch;
        }

        virtual void onMouseEvent(int ch)
        {
            NCF_UNUSED(ch);
        }

        virtual bool onEvent(int ch)
        {
            NCF_UNUSED(ch);
            return false;
        }

        inline int width() const
        {
            return m_rect.size.width;
        }

        inline int height() const
        {
            return m_rect.size.height;
        }

        inline int y() const
        {
            return m_rect.origin.y;
        }

        inline int x() const
        {
            return m_rect.origin.x;
        }

        //void setController(std::unique_ptr<Controller> controller);

        void setGeometry(const Rect& rect)
        {
            m_rect = rect;
            //TODO: Should probably redraw
        }

        Rect getGeometry()
        {
            return m_rect;
        }

        void setWindow(std::unique_ptr<ncurses::Window> window)
        {
            m_window = std::move(window);
        }

        void setSubWindow(std::unique_ptr<ncurses::Window> window)
        {
            m_subWindow = std::move(window);
        }

        ncurses::Window* getWindow() const
        {
            return m_window.get();
        }

        ncurses::Window* getSubWindow() const
        {
            return m_subWindow.get();
        }

        void hide();

        static std::vector<Widget*> WidgetList;

        bool shouldListenForKeyEvents = false;

        bool canFocus = true;

    private:
        Rect m_rect;

        std::unique_ptr<ncf::ncurses::Window> m_window;
        std::unique_ptr<ncf::ncurses::Window> m_subWindow;
};

}
#endif
