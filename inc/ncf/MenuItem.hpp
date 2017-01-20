#ifndef NCF_NCURSES_MENUITEM_H_
#define NCF_NCURSES_MENUITEM_H_

#include "ncf/Menu.hpp"
#include <menu.h>

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

        inline std::string name() const {
            return m_name;
        }

        inline std::string description () const {
            return m_description;
        }

        inline int index() const {
            return item_index(m_handle);
        }


        inline void setValue (bool value) {
            onError (::set_item_value(m_handle, value));
        }


        inline bool value () const {
            return ::item_value(m_handle);
        }

        inline bool visible () const {
            return ::item_visible(m_handle);
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
            return ::item_opts(m_handle);
        }

        inline void setOptions (Item_Options opts)
        {
            onError( set_item_opts(m_handle, opts) );
        }

        inline void onError (int err) {
            if (err != E_OK) {
                throw NCMenuException(err);
            }
        }

    private:
        ITEM* m_handle = NULL;

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

#endif
