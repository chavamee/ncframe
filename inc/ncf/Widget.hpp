#ifndef NCURSES_WIDGETS_H_
#define NCURSES_WIDGETS_H_

#include "ncf/Component.hpp"
#include "ncf/Geometry.hpp"

#include <algorithm>

//TODO: Check for inlinening opportunities

class Widget : public Component {
    public:
        Widget();

        Widget(const Rect& rect);

        virtual int onKeyEvent(int ch) = 0;

        virtual void onMouseEvent(int ch) = 0;

        virtual bool onEvent(int ch) = 0;

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

        void setGeometry(const Rect& rect)
        {
            m_rect = rect;
            //TODO: Should probably redraw
        }

        Rect getGeometry()
        {
            return m_rect;
        }

        void setWindow(std::unique_ptr<Window> window)
        {
            m_window = std::move(window);
        }

        void setSubWindow(std::unique_ptr<Window> window)
        {
            m_subWindow = std::move(window);
        }

        Window* getWindow() const
        {
            return m_window.get();
        }

        Window* getSubWindow() const
        {
            return m_subWindow.get();
        }

        static std::vector<Widget*> WidgetList;

        bool shouldListenForKeyEvents = false;

        bool canFocus = true;

    private:
        Rect m_rect;

        std::unique_ptr<Window> m_window;
        std::unique_ptr<Window> m_subWindow;
};

#endif
