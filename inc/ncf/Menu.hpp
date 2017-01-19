#ifndef NCURSES_MENU_BINDINGS_H_
#define NCURSES_MENU_BINDINGS_H_

#include "ncf/Window.hpp"
#include "ncf/Component.hpp"
#include "ncf/Widgets.hpp"
#include <menu.h>
#include <vector>
#include <memory>
#include <string.h>

#define CTRL(x) ((x) & 0x1f)

//TODO: Set items should have a limit

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
