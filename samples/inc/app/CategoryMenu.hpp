#ifndef APPLICATION_CTG_MENU_H_
#define APPLICATION_CTG_MENU_H_

#include "ncf/Menu.hpp"
#include "app/EntriesMenu.hpp"
#include "api/Feedly.hpp"

class CategoryMenu : public Menu {
    public:
        CategoryMenu()
        {
        }

        CategoryMenu(Feedly *server, Menu* entriesMenu) :
            m_entriesMenu {entriesMenu},
            m_server(server)
        {
        }

        CategoryMenu(const Rect& rect) :
            Menu(rect)
        {
        }

        virtual ~CategoryMenu()
        {
        }

        void onItemAction(MenuItem* item) override
        {
            std::vector<Feedly::Entry> entries = m_server->Entries(item->description(), false, 100);
            if (not entries.empty()) {
                lastReadEntryId = entries.front().id;
            }

            std::vector<MenuItem*> items;
            for (auto& entry : entries) {
                items.push_back(new EntryItem(entry));
            }
            m_entriesMenu->setItems(items);
        }

        void markCategoryRead()
        {
            m_server->MarkCategoryWithAction(currentItem().description(), READ, lastReadEntryId);
            std::vector<Feedly::Entry> entries = m_server->Entries(currentItem().description());
            std::vector<MenuItem*> items;
            for (auto& entry : entries) {
                items.push_back(new EntryItem{entry});
            }
            m_entriesMenu->setItems(items);
        }

        int onKeyEvent(int ch) override
        {
            switch(ch) {
                case 'r': markCategoryRead(); break;
                default: Menu::onKeyEvent(ch); break;
            }
            return 0;
        }

    private:
        Menu* m_entriesMenu = nullptr;
        Feedly* m_server = nullptr;
        std::string lastReadEntryId = "";
};

#endif
