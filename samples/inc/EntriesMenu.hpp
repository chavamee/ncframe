#ifndef APPLICATION_ENTRIES_MENU_H_
#define APPLICATION_ENTRIES_MENU_H_

#include "ncf/Menu.hpp"
#include "ncf/TextView.hpp"
#include "Feedly.hpp"
#include <iostream>
#include <fstream>


class EntriesMenu : public ncf::Menu {
    public:
        EntriesMenu() :
            Menu()
        {
        }

        EntriesMenu(ncf::TextView* view) :
            Menu(),
            m_previewTextView(view)
        {
        }

        void onItemSelected(ncf::Menu::Item* item) override
        {
            (void)item;
        }

        void ShowPreview(const std::string& preview)
        {
            std::ofstream sample("/home/chavamee/workspace/projects/active/ncframe/sample.html");

            sample << preview;

            sample.close();

            FILE* stream = popen(std::string("w3m -dump -cols " + std::to_string(COLS - 2) + " " + "/home/chavamee/workspace/projects/active/ncframe/sample.html").c_str(), "r");

            std::string content;

            if (stream)
            {
                char buffer[256];
                while (not feof(stream))
                {
                    if (fgets(buffer, 256, stream) not_eq NULL)
                    {
                        content.append(buffer);
                    }

                }
                pclose(stream);
            }
            m_previewTextView->setContent(content);
        }

    private:
        ncf::TextView* m_previewTextView = nullptr;
};

class EntryItem : public ncf::Menu::Item {
    public:
        EntryItem(Feedly::Entry& entry) : Item(entry.title, entry.id), m_entry{entry}
        {
        }

        bool action() override
        {
            static_cast<EntriesMenu*>(menu())->ShowPreview(m_entry.content);
            return true;
        }

    private:
        Feedly::Entry m_entry;
};

#endif
