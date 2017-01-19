#ifndef APPLICATION_ENTRIES_MENU_H_
#define APPLICATION_ENTRIES_MENU_H_

#include "ncf/Menu.hpp"
#include "ncf/TextView.hpp"
#include "api/Feedly.hpp"


class EntriesMenu : public Menu {
    public:
        EntriesMenu()
        {
        }

        EntriesMenu(TextView* view) :
            m_previewTextView(view)
        {
        }

        EntriesMenu(int rows, int cols, int y, int x) :
            Menu(rows, cols, y, x)
        {
        }

        void OnItemSelected(MenuItem* item) override
        {
            (void)item;
        }

        void ShowPreview(const std::string& preview)
        {
            m_previewTextView->SetContent(preview);
        }

    private:
        TextView* m_previewTextView = nullptr;
};

class EntryItem : public MenuItem {
    public:
        EntryItem(Feedly::Entry& entry) : MenuItem(entry.title, entry.id), m_entry{entry}
        {
        }

        bool Action() override
        {
            static_cast<EntriesMenu*>(Menu())->ShowPreview(m_entry.content);
            return true;
        }

    private:
        Feedly::Entry m_entry;
};

#endif
