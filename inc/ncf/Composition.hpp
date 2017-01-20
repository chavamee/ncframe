#ifndef NCURSES_COMPOSITIONS_H_
#define NCURSES_COMPOSITIONS_H_ value

#include "ncf/Component.hpp"

class Composition;

class Compositor {
    public:
        Compositor() = default;

        virtual ~Compositor() = default;

        virtual void compose() = 0;

        Composition* Composition = nullptr;
};

class Composition : public Component {
    public:
        Composition() = default;

        Composition(Compositor* compositor) :
            Compositor(compositor)
        {
        }

        virtual ~Composition()
        {
        }

        virtual void show() = 0;

        Compositor* Compositor = nullptr;
};

#endif /* ifndef NCURSES_LAYOUTS_COMPOSITIONS_H_ */
