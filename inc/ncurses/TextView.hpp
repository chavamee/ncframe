#ifndef NCURSES_TEXTVIEW_COMPONENT
#define NCURSES_TEXTVIEW_COMPONENT value

#include "ncurses/Component.hpp"
#include "ncurses/Window.hpp"
#include "ncurses/View.hpp"
#include <string>

//Should probably be widget
class TextView : public View {
    public:
        TextView();

        TextView(int height, int width);

        TextView(int height, int width, int y, int x);

        void Draw(std::unique_ptr<Window>& window) override;

        int OnKeyEvent(int ch) override;

        void OnMouseEvent(int ch) override;

        bool OnEvent(int ch) override;

    private:
        std::string m_content;
};

#endif /* ifndef NCURSES_TEXTVIEW_COMPONENT */
