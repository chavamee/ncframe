#ifndef NCURSES_WIDGETS_H_
#define NCURSES_WIDGETS_H_

#include "ncurses/Component.hpp"
#include <algorithm>

class Widget : public Component {
    public:
        Widget()
        {
            Widget::WidgetList.push_back(this);
        }

        Widget(int height, int width) :
            m_width(width),
            m_height(height)
        {
        }

        virtual int OnKeyEvent(int ch) = 0;

        virtual void OnMouseEvent(int ch) = 0;

        virtual bool OnEvent(int ch) = 0;

        bool ShouldListenForKeyEvents(bool op = true)
        {
            m_shouldListenForKeyEvents = op;
            return m_shouldListenForKeyEvents;
        }

        static std::vector<Widget*> WidgetList;

        bool m_shouldListenForKeyEvents = false;

        int Widgth() const
        {
            return m_width;
        }

        int Height() const
        {
            return m_height;
        }

        void SetHeight(int height)
        {
            m_height = height;
            //TODO: Redraw if already drawn
        }

        void SetWidth(int width)
        {
            m_width = width;
            //TODO: Redraw if already drawn
        }

        bool CanFocus = true;

        void SetWindow(std::unique_ptr<Window>& window)
        {
            m_window = move(window);
        }

        void SetSubWindow(std::unique_ptr<Window>& window)
        {
            m_subWindow = move(window);
        }

        Window& GetWindow() const
        {
            return *m_window;
        }

        Window& GetSubWindow() const
        {
            return *m_window;
        }

    private:
        int m_width = 0;
        int m_height = 0;

        std::unique_ptr<Window> m_window;
        std::unique_ptr<Window> m_subWindow;
};

class Row : public Component {
    public:
        void Draw(std::unique_ptr<Window>& mainWindow) override
        {
            for (auto& cmp : m_components) {
                cmp->Draw(mainWindow);
            }
        }

        void Add(Component* component, unsigned int pos = 0) override
        {
            m_components.insert(m_components.begin()+pos, component);
        }

        void Remove(Component* component) override
        {
            m_components.erase(std::find(m_components.begin(), m_components.end(), component));
        }

        Component* Child(int pos) override
        {
            return m_components.at(pos);
        }

        int ChildCount() override
        {
            return m_components.size();
        }

    private:
        std::vector<Component*> m_components;
};

class Column : public Component {
    public:
        void Draw(std::unique_ptr<Window>& mainWindow) override
        {
            for (auto& cmp : m_components) {
                cmp->Draw(mainWindow);
            }
        }

        void Add(Component* component, unsigned int pos = 0) override
        {
            m_components.insert(m_components.begin()+pos, component);
        }

        void Remove(Component* component) override
        {
            m_components.erase(std::find(m_components.begin(), m_components.end(), component));
        }

        Component* Child(int pos) override
        {
            return m_components.at(pos);
        }

        int ChildCount() override
        {
            return m_components.size();
        }

    private:
        std::vector<Component*> m_components;
};


#endif
