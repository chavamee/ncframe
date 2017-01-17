#include "ncurses/TextView.hpp"

using namespace std;

TextView::TextView()
{
}

TextView::TextView(int height, int width) :
    View(height, width)
{
}

TextView::TextView(int height, int width, int y, int x) :
    View(height, width)
{
    (void)y;
    (void)x;
}

void TextView::Draw(std::unique_ptr<Window>& window)
{
    std::unique_ptr<Window> subWindow = std::make_unique<Window>(
            window->Height()-2, window->Width()-2, window->OriginY()+1, window->OriginX()+1);
    window->PrintStr(m_content);
    SetWindow(window);
    SetSubWindow(subWindow);
    View::Draw(window);
}

int TextView::OnKeyEvent(int ch)
{
    switch (ch) {
        case KEY_UP:break;
    }
    return 0;
}

void TextView::OnMouseEvent(int ch)
{
    (void)ch;
}

bool TextView::OnEvent(int ch)
{
    (void)ch;
    return false;
}
