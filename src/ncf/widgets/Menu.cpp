
void Menu::onMouseEvent(int ch)
{
    (void)ch;
}

int Menu::onKeyEvent(int ch)
{
    switch(ch) {
        case KEY_DOWN      : return ::menu_driver(m_menu, REQ_DOWN_ITEM);
        case CTRL('N')     : return ::menu_driver(m_menu, REQ_NEXT_ITEM);
        case KEY_UP        : return ::menu_driver(m_menu, REQ_UP_ITEM);
        case CTRL('P')     : return ::menu_driver(m_menu, REQ_PREV_ITEM);

        case CTRL('T')     : return ::menu_driver(m_menu, REQ_TOGGLE_ITEM);

                             /*
                              * Depending on the terminal, the Enter/Send key will return one of
                              * the following:
                              */
        case '\r'          :
        case '\n'          :
        case KEY_ENTER     : _invokeAction(currentItem()); return 1;

        case KEY_HOME      : return ::menu_driver(m_menu, REQ_FIRST_ITEM);
        case KEY_LEFT      : return ::menu_driver(m_menu, REQ_LEFT_ITEM);
        case KEY_RIGHT     : return ::menu_driver(m_menu, REQ_RIGHT_ITEM);
        case KEY_END       : return ::menu_driver(m_menu, REQ_LAST_ITEM);
    }
    return 0;
}

bool Menu::onEvent(int ch)
{
    (void)ch;
    return false;
}


void Menu::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (window.get() != nullptr) {

        keypad(window->getHandle(), true);
        meta(window->getHandle(), true);

        //TODO: initializeItems()

        m_handle = new_menu(_unpackItems(m_items));
        if (m_handle == NULL) {
            onError(E_SYSTEM_ERROR);
        }

        set_menu_win(m_handle, window->getHandle());

        subWindow = make_unique<Window>(
                *window,
                window->height()-2, window->width()-2, 1, 1,
                false
                );

        set_menu_sub(m_handle, subWindow->getHandle());

        //TODO: These should be treated as defaults. Maybe do at construction
        // to ensure that after construction if the user needs to change the
        // format this will not conflict.
        setFormat({.height = window->height() - 2, .width = 1});
        setMark(m_itemMark ? m_itemMark : "*");

        Application* app = Application::getApplication();
        if (app) {
            ::set_menu_fore(m_handle, app->foregrounds());
            ::set_menu_back(m_handle, app->backgrounds());
            ::set_menu_grey(m_handle, app->inactives());
        }

        post();
        window->refresh();

        setWindow(std::move(window));
        setSubWindow(std::move(subWindow));
    } else {
        //TODO: Define defaults
    }

    m_isDrawn = true;
}
