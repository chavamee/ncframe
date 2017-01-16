#ifndef NCURSES_LAYOUTS_H_
#define NCURSES_LAYOUTS_H_ value

#include "ncurses/Composition.hpp"
#include "ncurses/Widgets.hpp"
#include <algorithm>

class LayoutCompositor : public Compositor {
    public:
        LayoutCompositor();

        virtual ~LayoutCompositor();

        virtual void Compose() override = 0;
};

class Layout : public Composition {
    public:
        Layout(LayoutCompositor* compositor);

        Layout(unsigned int height, unsigned int width, LayoutCompositor* compositor);

        virtual ~Layout();

        virtual void Show() = 0;

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

        void Draw(std::unique_ptr<Window>& mainWindow) override;

        void Show() override;

        void Add(Component* component, unsigned int pos = 0) override;

        void Remove(Component* component) override;

        Component* Child(int pos) override;

        int ChildCount() override;

    private:
        std::vector<Component*> m_components;
};

class UniformRowCompositor : public LayoutCompositor {
    public:
        UniformRowCompositor();

        virtual ~UniformRowCompositor();

        void Compose() override;

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

        void Draw(std::unique_ptr<Window>& mainWindow) override;

        void Show() override;

        void Add(Component* component, unsigned int pos = 0) override;

        void Remove(Component* component) override;

        Component* Child(int pos) override;

        int ChildCount() override;

    private:
        std::vector<Component*> m_components;
};


class UniformColumnCompositor : public LayoutCompositor {
    public:
        UniformColumnCompositor();

        virtual ~UniformColumnCompositor();

        void Compose() override;

    private:
        Column m_column;
};

class ResponsiveFormat : public Compositor {
};

#endif /* ifndef NCURSES_ROWLAYOUT_COMPONENT_H_ */
