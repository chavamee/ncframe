#ifndef NCURSES_MENU_BINDINGS_H_
#define NCURSES_MENU_BINDINGS_H_

#include "ncf/ncurses/Window.hpp"
#include "ncf/ncurses/NCMenuException.hpp"
#include "common/platform.h"

#include <menu.h>

#include <cstring>

#include <vector>
#include <memory>

#define CTRL(x) ((x) & 0x1f)

//TODO: Set items should have a limit
//TODO: Replace Menu_Options with concrete struct
namespace ncf {
namespace ncurses {

class Menu {
    class MenuItem {
        friend Menu;

    public:
        MenuItem();

        MenuItem(
                const std::string& name,
                const std::string& description
                );

        /**
         * Copy Constructor
         */
        MenuItem(const MenuItem& item);

        virtual ~MenuItem();

        MenuItem& operator=(const MenuItem& other);

        inline std::string name() const {
            return m_name;
        }

        inline std::string description () const {
            return m_description;
        }

        inline int index() const {
            return item_index(m_item);
        }


        inline void setValue (bool value) {
            onError (::set_item_value(m_item, value));
        }


        inline bool value () const {
            return ::item_value(m_item);
        }

        inline bool visible () const {
            return ::item_visible(m_item);
        }

        inline Menu* menu() const
        {
            return m_menu;
        }

        inline bool hasMenu() const
        {
            return m_menu ? true : false;
        }

        virtual bool action()
        {
            return false;
        }

        inline Item_Options options()
        {
            return ::item_opts(m_item);
        }

        inline void setOptions (Item_Options opts)
        {
            onError( set_item_opts(m_item, opts) );
        }

        inline void onError (int err) {
            if (err != E_OK) {
                throw NCMenuException(err);
            }
        }

    private:
        ITEM* m_item = NULL;

        /*
         * TODO: Clean up explanation
         * ncurses does not copy the name or description buffers and only
         * keeps pointers to them. The strings are managed internally to
         * avoid invalid memory derefrence by ncurses and managing their lifetime.
         */
        std::string m_name = "";
        std::string m_description = "";

        Menu* m_menu = nullptr;
    };

    public:
        Menu();

        Menu(const Rect& rect);

        Menu(const Rect& rect, std::vector<MenuItem*>& items);

        virtual ~Menu();

        void setItems(std::vector<MenuItem*>& items);

        void setWindow(Window& win);

        void setSubWindow(Window& win);

        void setWindow(std::unique_ptr<Window> win);

        void setSubWindow(std::unique_ptr<Window> win);

        inline MENU* getHandle() const
        {
            return m_menu;
        }

        void optionsOff(Menu_Options opts)
        {
            onError( ::menu_opts_off(m_menu, opts) );
        }

        void optionsOn(Menu_Options opts)
        {
            onError ( ::menu_opts_on(m_menu, opts) );
        }

        MenuItem& currentItem()
        {
            return *(m_items.at( item_index(current_item(m_menu)) ));
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
            onError (::scale_menu (m_menu, &height, &width));
            return {.height = height, .width = width};
        }

        inline void onError (int err) const {
            if (err != E_OK)
                throw NCMenuException("Menu error", err);
        }

        // Remove the menu from the screen
        inline void unpost (void) {
            onError (::unpost_menu (m_menu));
            m_isPosted = false;
        }

        // Post the menu to the screen if flag is true, unpost it otherwise
        inline void post() {
            onError (::post_menu(m_menu));
            m_isPosted = true;
        }

        // Set the format of this menu
        inline void setFormat(const Size& size) {
            onError (::set_menu_format(m_menu, (int)size.height, (int)size.width));
        }

        // Get the format of this menu
        Size format() {
            int height = 0;
            int width = 0;
            ::menu_format(m_menu, &height, &width);
            return {.height = height, .width = width};
        }

        // Items of the menu
        std::vector<MenuItem*> items() const {
            return m_items;
        }

        // Get the number of items in this menu
        inline int count() const {
            return ::item_count(m_menu);
        }

        // Get the marker string
        inline const char* mark() const {
            return ::menu_mark(m_menu);
        }

        // Set the marker string
        inline void setMark(const char* marker) {
            onError (::set_menu_mark (m_menu, marker));
        }

        // Get the name of the request code c
        /*inline static const char* request_name(int c) {
            return ::menu_request_name(c);
        }*/

        // Get the current pattern
        inline char* pattern() const {
            return ::menu_pattern(m_menu);
        }

        // true if there is a pattern match, false otherwise.
        bool setPattern (const char *pattern);

        // set the default attributes for the menu
        // i.e. set fore, back and grey attribute
        virtual void setDefaultAttributes();

        //TODO: Should return more concrete type
        // Get the menus background attributes
        inline chtype background() const {
            return ::menu_back(m_menu);
        }

        // Get the menus foreground attributes
        inline chtype foreground() const {
            return ::menu_fore(m_menu);
        }

        // Get the menus grey attributes (used for unselectable items)
        inline chtype grey() const {
            return ::menu_grey(m_menu);
        }

        // Set the menus background attributes
        inline chtype setBackground(chtype a) {
            return ::set_menu_back(m_menu,a);
        }

        // Set the menus foreground attributes
        inline chtype setForeground(chtype a) {
            return ::set_menu_fore(m_menu,a);
        }

        // Set the menus grey attributes (used for unselectable items)
        inline chtype setGrey(chtype a) {
            return ::set_menu_grey(m_menu,a);
        }

        inline Menu_Options options() const {
            return ::menu_opts(m_menu);
        }

        inline void setOptions (Menu_Options opts) {
            onError (::set_menu_opts (m_menu,opts));
        }

        inline int padding() const {
            return ::menu_pad(m_menu);
        }

        inline void setPadding (int padch) {
            onError (::set_menu_pad (m_menu, padch));
        }

        // Position the cursor to the current item
        inline void positionCursor () const {
            onError (::pos_menu_cursor (m_menu));
        }

        inline void setCurrentItem(MenuItem& item);

        // Get the current top row of the menu
        inline int topRow (void) const {
            return ::top_row (m_menu);
        }

        // Set the current top row of the menu
        inline void setTopRow (int row) {
            onError (::set_top_row (m_menu, row));
        }

        // spacing control
        // Set the spacing for the menu
        inline void setSpacing(int spc_description,
                int spc_rows,
                int spc_columns) {
            onError(::set_menu_spacing(m_menu,
                        spc_description,
                        spc_rows,
                        spc_columns));
        }

        // Get the spacing info for the menu
        inline void spacing(int& spc_description,
                int& spc_rows,
                int& spc_columns) const {
            onError(::menu_spacing(m_menu,
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
        MENU* m_menu = NULL;

        const char* m_itemMark = "*";

        bool m_isDrawn = false;
        bool m_hasFocus = false;
        bool m_isPosted = false;

        std::vector<MenuItem*> m_items;

        std::unique_ptr<Window> m_window;
        std::unique_ptr<Window> m_subWindow;

        ITEM** _unpackItems(std::vector<MenuItem*>& items);
        bool _invokeAction(MenuItem& item);
};

}
}
#endif
