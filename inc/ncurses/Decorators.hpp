#ifndef NCURSES_DECORATORS_H_
#define NCURSES_DECORATORS_H_ value

#include "ncurses/Component.hpp"

class Decorator : public Component {
    public:
        Decorator(Component* component) :
            m_component(component)
        {
        }

        void Draw(std::unique_ptr<Window>& mainWindow) override
        {
            m_component->Draw(mainWindow);
        }

    private:
        Component* m_component = nullptr;
};

class Border : public Decorator {
    public:
        Border(Component* component) :
            Decorator(component)
        {
        }
        void Draw(std::unique_ptr<Window>& mainWindow) override
        {
            mainWindow->Frame();
            Decorator::Draw(mainWindow);
        }
};

#endif /* ifndef NCURSES_DECORATORS_H_ */
