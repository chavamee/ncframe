#ifndef NCURSES_MENU_BINDINGS_H_
#define NCURSES_MENU_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Component.hpp"
#include "ncf/Widgets.hpp"
#include "ncf/NCException.hpp"
#include <menu.h>
#include <vector>
#include <memory>
#include <string.h>

#define CTRL(x) ((x) & 0x1f)

//TODO: Set items should have a limit
//TODO: Place all calls to ncurses api on the OnError callback

class Menu;

class MenuItem {
    friend Menu;

    public:
        MenuItem();

        MenuItem(
            std::string name,
            std::string description
                );

        /**
         * Copy Constructor
         */
        MenuItem(const MenuItem& item);

        virtual ~MenuItem();

        MenuItem& operator=(const MenuItem& other);

        inline std::string Name() const {
            return m_name;
        }

        inline std::string Description () const {
            return m_description;
        }

        inline int Index() const {
            return item_index(m_handle);
        }

        inline void SetValue (bool f) {
            set_item_value(m_handle, f);
        }

        inline bool Value () const {
            return item_value(m_handle);
        }

        inline bool Visible () const {
            return item_visible(m_handle);
        }

        inline Menu* Menu() const
        {
            return m_menu;
        }

        inline bool HasMenu() const
        {
            return m_menu ? true : false;
        }

        virtual bool Action()
        {
            return false;
        }

        inline Menu_Options options();

        inline void set_options (Menu_Options opts);

    private:
        ITEM* m_handle = NULL;

        /*
         * ncurses does not copy the name or description buffers and only
         * keeps pointers to them. The strings are managed internally to
         * avoid invalid memory derefrence by ncurses and managing their lifetime.
         */
        std::string m_name = "";
        std::string m_description = "";

        class Menu* m_menu = nullptr;
};

class Menu : public Widget {
    public:
        Menu();

        Menu(
            int rows,
            int cols,
            int y,
            int x
            );

        Menu(
            int rows,
            int cols,
            int y,
            int x,
            std::vector<MenuItem*>& items
            );

        virtual ~Menu();

        void SetItems(std::vector<MenuItem*>& items);

        inline MENU* GetHandle() const
        {
            return m_handle;
        }

        void Draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        void OnMouseEvent (int ch) override;

        int OnKeyEvent(int ch) override;

        bool OnEvent(int ch) override;

        void OptionsOff(Menu_Options opts)
        {
            ::menu_opts_off(m_handle, opts);
        }

        void OptionsOn(Menu_Options opts)
        {
            ::menu_opts_on(m_handle, opts);
        }

        MenuItem& CurrentItem()
        {
            return *(m_items.at( item_index(current_item(m_handle)) ));
        }

        virtual void OnMenuPosted()
        {
        }

        virtual void OnMenuUnposted()
        {
        }

        virtual void OnItemSelected(MenuItem* item)
        {
            (void)item;
        }

        virtual void OnItemDeselected(MenuItem* item)
        {
            (void)item;
        }

        virtual void OnItemAction(MenuItem* item)
        {
            (void)item;
        }

        //TODO: This shoudl return
        inline void Scale(int& height, int& width) const
        {
            OnError (::scale_menu (m_handle, &height, &width));
        }

        inline void OnError (int err) const {
            if (err != E_OK)
                throw NCException("Menu error", err);
        }

        // Remove the menu from the screen
        inline void Unpost (void) {
            OnError (::unpost_menu (m_handle));
        }

        // Post the menu to the screen if flag is true, unpost it otherwise
        inline void Post() {
            OnError (::post_menu(m_handle));
        }

        // Set the format of this menu
        inline void SetFormat(int mrows, int mcols) {
            OnError (::set_menu_format(m_handle, mrows, mcols));
        }

        // Get the format of this menu
        inline void Format(int& rows,int& ncols) {
            ::menu_format(m_handle,&rows,&ncols);
        }

        // Items of the menu
        inline std::vector<MenuItem*> Items() const {
            return m_items;
        }

        // Get the number of items in this menu
        inline int Count() const {
            return ::item_count(m_handle);
        }

        // Get the marker string
        inline const char* Mark() const {
            return ::menu_mark(m_handle);
        }

        // Set the marker string
        inline void SetMark(const char *marker) {
            OnError (::set_menu_mark (m_handle, marker));
        }

        // Get the name of the request code c
        /*inline static const char* request_name(int c) {
            return ::menu_request_name(c);
        }*/

        // Get the current pattern
        inline char* Pattern() const {
            return ::menu_pattern(m_handle);
        }

        // true if there is a pattern match, false otherwise.
        bool SetPattern (const char *pat);

        // set the default attributes for the menu
        // i.e. set fore, back and grey attribute
        virtual void SetDefaultAttributes();

        //TODO: Should return more concrete type
        // Get the menus background attributes
        inline chtype Background() const {
            return ::menu_back(m_handle);
        }

        // Get the menus foreground attributes
        inline chtype Foreground() const {
            return ::menu_fore(m_handle);
        }

        // Get the menus grey attributes (used for unselectable items)
        inline chtype Grey() const {
            return ::menu_grey(m_handle);
        }

        // Set the menus background attributes
        inline chtype SetBackground(chtype a) {
            return ::set_menu_back(m_handle,a);
        }

        // Set the menus foreground attributes
        inline chtype SetForeground(chtype a) {
            return ::set_menu_fore(m_handle,a);
        }

        // Set the menus grey attributes (used for unselectable items)
        inline chtype SetGrey(chtype a) {
            return ::set_menu_grey(m_handle,a);
        }

        inline Menu_Options options() const {
            return ::menu_opts(m_handle);
        }

        inline void SetOptions (Menu_Options opts) {
            OnError (::set_menu_opts (m_handle,opts));
        }

        inline int Padding() const {
            return ::menu_pad(m_handle);
        }

        inline void SetPadding (int padch) {
            OnError (::set_menu_pad (m_handle, padch));
        }

        // Position the cursor to the current item
        inline void PositionCursor () const {
            OnError (::pos_menu_cursor (m_handle));
        }

        // Set the current item
        inline void SetCurrentItem(MenuItem& I) {
            OnError (::set_current_item(m_handle, I.m_handle));
        }

        // Get the current top row of the menu
        inline int TopRow (void) const {
            return ::top_row (m_handle);
        }

        // Set the current top row of the menu
        inline void SetTopRow (int row) {
            OnError (::set_top_row (m_handle, row));
        }

        // spacing control
        // Set the spacing for the menu
        inline void SetSpacing(int spc_description,
                int spc_rows,
                int spc_columns) {
            OnError(::set_menu_spacing(m_handle,
                        spc_description,
                        spc_rows,
                        spc_columns));
        }

        // Get the spacing info for the menu
        inline void Spacing(int& spc_description,
                int& spc_rows,
                int& spc_columns) const {
            OnError(::menu_spacing(m_handle,
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

    private:
        ITEM** unpackItems(std::vector<MenuItem*>& items);
        bool invokeAction(MenuItem& item);

        MENU* m_handle = NULL;
        const char* m_itemMark = "*";

        bool m_isDrawn = false;

        std::vector<MenuItem*> m_items;
        bool m_hasFocus = false;
};

#endif
