#include "ncurses/TextView.hpp"

using namespace std;

TextView::TextView() :
    m_mainWindow{},
    m_subWindow{}
{
}

TextView::TextView(int height, int width)
    //View(height, width)
{
}

TextView::TextView(int height, int width, int y, int x) :
    //Widget(height, width),
    m_subWindow{}
{
    (void)y;
    (void)x;
}

void TextView::Draw(std::unique_ptr<Window>& mainWindow)
{
    if (mainWindow.get() != nullptr) {
        m_mainWindow = move(mainWindow);
    } else {
        m_mainWindow  = make_unique<Window>(10, 10, 0, 0);
    }

    m_subWindow = std::make_unique<Window>(
            m_mainWindow->Height()-2, m_mainWindow->Width()-2, m_mainWindow->OriginY()+1, m_mainWindow->OriginX()+1);
    m_pad = make_unique<Pad>(m_mainWindow->Height(), m_mainWindow->Width());
    m_pad->SetWindow(move(m_mainWindow));
    m_pad->SetSubWindow(move(m_subWindow));
    m_pad->PrintStr(m_content);
    m_pad->Refresh();
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
