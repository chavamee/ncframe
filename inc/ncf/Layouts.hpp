#ifndef NCURSES_LAYOUTS_H_
#define NCURSES_LAYOUTS_H_ value

#include "ncf/Composition.hpp"
#include "ncf/Widget.hpp"
#include "ncf/Row.hpp"
#include "ncf/Column.hpp"
#include <algorithm>

class LayoutCompositor : public Compositor {
    public:
        LayoutCompositor();

        virtual ~LayoutCompositor();

        virtual void compose() override = 0;
};

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

class RowLayout : public Layout {
    public:
        RowLayout();

        RowLayout(unsigned int height, unsigned int width);

        RowLayout(unsigned int height, unsigned int width, LayoutCompositor* compositor);

        virtual ~RowLayout();

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        void show() override;

        void add(Component* component, unsigned int pos = 0) override;

        void remove(Component* component) override;

        Component* child(std::size_t pos) override;

        std::size_t childCount() override;

    private:
        std::vector<Component*> m_components;
};

class UniformRowCompositor : public LayoutCompositor {
    public:
        UniformRowCompositor();

        virtual ~UniformRowCompositor();

        void compose() override;

    private:
        Row m_row;
};

class ColumnLayout : public Layout {
    public:
        ColumnLayout();

        ColumnLayout(LayoutCompositor* compositor);

        ColumnLayout(
                unsigned int height,
                unsigned int width,
                LayoutCompositor* compositor
                );

        virtual ~ColumnLayout();

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        void show() override;

        void add(Component* component, unsigned int pos = 0) override;

        void remove(Component* component) override;

        Component* child(std::size_t pos) override;

        std::size_t childCount() override;

    private:
        std::vector<Component*> m_components;
};


class UniformColumnCompositor : public LayoutCompositor {
    public:
        UniformColumnCompositor();

        virtual ~UniformColumnCompositor();

        void compose() override;

    private:
        Column m_column;
};

class ResponsiveFormat : public Compositor {
};

#endif /* ifndef NCURSES_ROWLAYOUT_COMPONENT_H_ */
