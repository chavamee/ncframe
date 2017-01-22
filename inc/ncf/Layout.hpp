#ifndef NCURSES_LAYOUTS_H_
#define NCURSES_LAYOUTS_H_ value

#include "ncf/Composition.hpp"
#include "ncf/Widget.hpp"

#include <algorithm>

class LayoutCompositor;

class Layout : public Composition {
    public:
        Layout(LayoutCompositor* compositor);

        Layout(unsigned int height, unsigned int width, LayoutCompositor* compositor);

        virtual ~Layout();

        virtual void show() = 0;

        int MaxHeight = LINES-1;
        int MaxWidth  = COLS-1;

        int MinHeight = 0;
        int MinWidth  = 0;

    protected:
        int m_effectiveHeight = LINES-1;
        int m_effectiveWidth  = COLS-1;
};


class LayoutCompositor : public Compositor {
    public:
        LayoutCompositor();

        virtual ~LayoutCompositor();

        virtual void compose() override = 0;
};

#endif /* ifndef NCURSES_ROWLAYOUT_COMPONENT_H_ */
