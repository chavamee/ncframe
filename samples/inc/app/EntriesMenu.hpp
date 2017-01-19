#ifndef APPLICATION_ENTRIES_MENU_H_
#define APPLICATION_ENTRIES_MENU_H_

#include "ncf/Menu.hpp"
#include "ncf/TextView.hpp"
#include "api/Feedly.hpp"
#include <iostream>
#include <fstream>


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
            m_previewTextView->SetContent(content);
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
