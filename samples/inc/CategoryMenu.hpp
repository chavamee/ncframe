#ifndef APPLICATION_CTG_MENU_H_
#define APPLICATION_CTG_MENU_H_

#include "ncf/Menu.hpp"
#include "EntriesMenu.hpp"
#include "Feedly.hpp"

class CategoryMenu : public ncf::Menu {
    public:
        CategoryMenu() :
            Menu()
        {
        }

        CategoryMenu(Feedly *server, ncf::Menu* entriesMenu) :
            Menu(),
            m_entriesMenu {entriesMenu},
            m_server(server)
        {
        }

        virtual ~CategoryMenu()
        {
        }

        void onItemAction(ncf::Menu::Item* item) override
        {
            std::vector<Feedly::Entry> entries = m_server->Entries(item->description(), false, 100);
            if (not entries.empty()) {
                lastReadEntryId = entries.front().id;
            }

            std::vector<ncf::Menu::Item*> items;
            for (auto& entry : entries) {
                items.push_back(new EntryItem(entry));
            }
            m_entriesMenu->setItems(items);
        }

        void markCategoryRead()
        {
            m_server->MarkCategoryWithAction(currentItem().description(), READ, lastReadEntryId);
            std::vector<Feedly::Entry> entries = m_server->Entries(currentItem().description());
            std::vector<ncf::Menu::Item*> items;
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
