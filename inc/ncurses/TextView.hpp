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

        void Draw(std::unique_ptr<Window>& mainWindow) override;

        void SetContent(const std::string& str)
        {
            m_content = str;
            Redraw();
        }

        void Redraw()
        {
            if (m_pad) {
                m_pad->Clear();
                m_pad->PrintStr(m_content);
                m_pad->Refresh();
            }
        }

        int OnKeyEvent(int ch) override;

        void OnMouseEvent(int ch) override;

        bool OnEvent(int ch) override;

    private:
        std::unique_ptr<Window> m_mainWindow;
        std::unique_ptr<Window> m_subWindow;
        std::string m_content;
        std::unique_ptr<Pad> m_pad;
};

#endif /* ifndef NCURSES_TEXTVIEW_COMPONENT */
