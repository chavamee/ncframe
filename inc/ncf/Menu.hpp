#ifndef NCURSES_MENU_BINDINGS_H_
#define NCURSES_MENU_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Component.hpp"
#include "ncf/Widget.hpp"
#include "ncf/NCMenuException.hpp"
#include "ncf/MenuItem.hpp"

#include <menu.h>

#include <cstring>

#include <vector>
#include <memory>

#define CTRL(x) ((x) & 0x1f)

//TODO: Set items should have a limit
//TODO: Replace Menu_Options with concrete struct

class MenuItem;

class Menu : public Widget {
    public:
        Menu();

        Menu(const Rect& rect);

        Menu(const Rect& rect, std::vector<MenuItem*>& items);

        virtual ~Menu();

        void setItems(std::vector<MenuItem*>& items);

        inline MENU* getHandle() const
        {
            return m_handle;
        }

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        void onMouseEvent (int ch) override;

        int onKeyEvent(int ch) override;

        bool onEvent(int ch) override;

        void optionsOff(Menu_Options opts)
        {
            onError( ::menu_opts_off(m_handle, opts) );
        }

        void optionsOn(Menu_Options opts)
        {
            onError ( ::menu_opts_on(m_handle, opts) );
        }

        MenuItem& currentItem()
        {
            return *(m_items.at( item_index(current_item(m_handle)) ));
        }

        virtual void onMenuPosted()
        {
        }

        virtual void onMenuUnposted()
        {
        }

        virtual void onItemSelected(MenuItem* item)
        {
            NCF_UNUSED(item);
        }

        virtual void onItemDeselected(MenuItem* item)
        {
            NCF_UNUSED(item);
        }

        virtual void onItemAction(MenuItem* item)
        {
            NCF_UNUSED(item);
        }

        Size scale() const
        {
            int height = 0;
            int width = 0;
            onError (::scale_menu (m_handle, &height, &width));
            return {.height = height, .width = width};
        }

        inline void onError (int err) const {
            if (err != E_OK)
                throw NCMenuException("Menu error", err);
        }

        // Remove the menu from the screen
        inline void unpost (void) {
            onError (::unpost_menu (m_handle));
            m_isPosted = false;
        }

        // Post the menu to the screen if flag is true, unpost it otherwise
        inline void post() {
            onError (::post_menu(m_handle));
            m_isPosted = true;
        }

        // Set the format of this menu
        inline void setFormat(const Size& size) {
            onError (::set_menu_format(m_handle, size.height, size.width));
        }

        // Get the format of this menu
        Size format() {
            int height = 0;
            int width = 0;
            ::menu_format(m_handle, &height, &width);
            return {.height = height, .width = width};
        }

        // Items of the menu
        std::vector<MenuItem*> items() const {
            return m_items;
        }

        // Get the number of items in this menu
        inline int count() const {
            return ::item_count(m_handle);
        }

        // Get the marker string
        inline const char* mark() const {
            return ::menu_mark(m_handle);
        }

        // Set the marker string
        inline void setMark(const char* marker) {
            onError (::set_menu_mark (m_handle, marker));
        }

        // Get the name of the request code c
        /*inline static const char* request_name(int c) {
            return ::menu_request_name(c);
        }*/

        // Get the current pattern
        inline char* pattern() const {
            return ::menu_pattern(m_handle);
        }

        // true if there is a pattern match, false otherwise.
        bool setPattern (const char *pattern);

        // set the default attributes for the menu
        // i.e. set fore, back and grey attribute
        virtual void setDefaultAttributes();

        //TODO: Should return more concrete type
        // Get the menus background attributes
        inline chtype background() const {
            return ::menu_back(m_handle);
        }

        // Get the menus foreground attributes
        inline chtype foreground() const {
            return ::menu_fore(m_handle);
        }

        // Get the menus grey attributes (used for unselectable items)
        inline chtype grey() const {
            return ::menu_grey(m_handle);
        }

        // Set the menus background attributes
        inline chtype setBackground(chtype a) {
            return ::set_menu_back(m_handle,a);
        }

        // Set the menus foreground attributes
        inline chtype setForeground(chtype a) {
            return ::set_menu_fore(m_handle,a);
        }

        // Set the menus grey attributes (used for unselectable items)
        inline chtype setGrey(chtype a) {
            return ::set_menu_grey(m_handle,a);
        }

        inline Menu_Options options() const {
            return ::menu_opts(m_handle);
        }

        inline void setOptions (Menu_Options opts) {
            onError (::set_menu_opts (m_handle,opts));
        }

        inline int padding() const {
            return ::menu_pad(m_handle);
        }

        inline void setPadding (int padch) {
            onError (::set_menu_pad (m_handle, padch));
        }

        // Position the cursor to the current item
        inline void positionCursor () const {
            onError (::pos_menu_cursor (m_handle));
        }

        inline void setCurrentItem(MenuItem& item);

        // Get the current top row of the menu
        inline int topRow (void) const {
            return ::top_row (m_handle);
        }

        // Set the current top row of the menu
        inline void setTopRow (int row) {
            onError (::set_top_row (m_handle, row));
        }

        // spacing control
        // Set the spacing for the menu
        inline void setSpacing(int spc_description,
                int spc_rows,
                int spc_columns) {
            onError(::set_menu_spacing(m_handle,
                        spc_description,
                        spc_rows,
                        spc_columns));
        }

        // Get the spacing info for the menu
        inline void spacing(int& spc_description,
                int& spc_rows,
                int& spc_columns) const {
            onError(::menu_spacing(m_handle,
                        &spc_description,
                        &spc_rows,
                        &spc_columns));
        }

        // Decorations
        /*inline void frame(const char *title=NULL, const char* btitle=NULL) {
            if (b_framed)
                NCursesPanel::frame(title,btitle);
            else
                OnError(E_SYSTEM_ERROR);
        }

        inline void boldframe(const char *title=NULL, const char* btitle=NULL) {
            if (b_framed)
                NCursesPanel::boldframe(title,btitle);
            else
                OnError(E_SYSTEM_ERROR);
        }

        inline void label(const char *topLabel, const char *bottomLabel) {
            if (b_framed)
                NCursesPanel::label(topLabel,bottomLabel);
            else
                OnError(E_SYSTEM_ERROR);
        }*/

        inline bool isPosted()
        {
            return m_isPosted;
        }

    private:
        MENU* m_handle = NULL;

        const char* m_itemMark = "*";

        bool m_isDrawn = false;
        bool m_hasFocus = false;
        bool m_isPosted = false;

        std::vector<MenuItem*> m_items;

        ITEM** _unpackItems(std::vector<MenuItem*>& items);
        bool _invokeAction(MenuItem& item);
};

#endif
