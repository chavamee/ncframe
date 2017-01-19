/**
 * @file
 * Contains the Feedly class which interaces with the Feedly Web API and defines
 * various types to facilitate usage.
 */
#ifndef FEEDLY_H_
#define FEEDLY_H_

#include <string>
#include <map>
#include <vector>

/**
 * Various actions that can be applied to entries and categories.
 *
 * Note that SAVED and UNSAVED are not available for categories
 */
enum Actions {
    READ,
    UNREAD,
    SAVED,
    UNSAVED
};

/**
 * @class Interface with the Feedly API
 */
class Feedly {
    public:
        struct User {
            std::string id;
            std::string authToken;
        };

        struct Entry {
            std::string content;
            std::string title;
            std::string id;
            std::string originURL;
            std::string originTitle;

            Entry(
                    std::string p_content,
                    std::string p_title,
                    std::string p_id,
                    std::string p_originURL,
                    std::string p_originTitle) :
                content(p_content),
                title(p_title),
                id(p_id),
                originURL(p_originURL),
                originTitle(p_originTitle)
            {
            }

            Entry(const Entry& other) :
                content(other.content),
                title(other.title),
                id(other.id),
                originURL(other.originURL),
                originTitle(other.originTitle)
            {
            }

            Entry(Entry&& other) :
                content(other.content),
                title(other.title),
                id(other.id),
                originURL(other.originURL),
                originTitle(other.originTitle)
            {
            }

        };

        class Category {
            std::string id;
        };

        class Feed {
        };

        /*
         * Default constructor is not allowed
         */
        Feedly() = delete;

        /**
         * Construct a Feedly wrapper with the given user.
         *
         * @param user  User to accesss Feedly API with
         */
        Feedly(User& user);

        /**
         * Ensure that we can Authenticate with the Feedly API.
         *
         * @return - true if Authentication was sucessful.
         *         - false if Authentication failed.
         */
        bool Authenticate();

        /**
         * Return the available categories.
         *
         * @return a map with the category label as a key and the category id as a value
         */
        std::map<std::string, std::string> Categories() const;

        /**
         * Mark a single entry with an action.
         *
         * @param entryId  ID of the entry to apply the action to
         * @param action  the action to apply
         */
        void MarkEntryWithAction(const std::string& entryId, Actions action);

        /**
         * Mark a multiple entries with an action.
         *
         * @param entryId  list of IDs for the entries to apply the action to
         * @param action  the action to apply
         */
        void MarkEntriesWithAction(const std::vector<std::string>& entryIds, Actions action);

        /**
         * Mark a single category with an action.
         *
         * @param categoryId  ID of the category to apply the action to
         * @param action      the action to apply
         */
        void MarkCategoryWithAction(const std::string& categoryId, Actions action, const std::string& lastReadEntryId = "");

        /**
         * Subscribe to a feed
         *
         * @param feed       the feed to subscribe to
         * @param title      the title for the new feed
         * @param categories an optional list of category ids that the feed should be added to
         */
        void AddSubscription(const std::string& feed, const std::string& title, const std::vector<std::string> *const categories = nullptr);

        /**
         * Return entries for a specific category.
         *
         * @param categoryId     the category to fetch entries from
         * @param sortByOldest   return the list of entries ordered by oldest
         * @param count          number of entries to fetch
         * @param unreadOnly     fetch only unread entries
         * @param continuationId fetch entries after a specific id
         * @param newerThan      fetch entries newer than timestamp in ms
         *
         * @return a list of entries
         */
        std::vector<Entry> Entries(
                const std::string& categoryId,
                bool sortByOldest = false,
                unsigned int count = 20,
                bool unreadOnly = true,
                std::string continuationId = "",
                unsigned long newerThan = 0
                );

        /**
         * Get a list of unread counts
         */
        void UnreadCounts();

        /**
         * Check if Feedly is available
         *
         * @return true if we can reach feedly.com, false otherwise
         */
        static bool IsAvailable();

    private:
        const std::string m_rootUrl = "https://cloud.feedly.com/v3";
        Feedly::User m_user;
};

#endif /* ifndef FEEDLY_H_ */
