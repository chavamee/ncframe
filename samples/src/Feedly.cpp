#include "Feedly.hpp"

#include "json.hpp"
#include <cpr/cpr.h>

#include <fstream>

using namespace std;
using json = nlohmann::json;

const string FeedlyUrl = "https://feedly.com";

inline string ActionToStr(Actions action)
{
    switch (action) {
        case Actions::READ:
            return "markAsRead";
        case Actions::UNREAD:
            return "undoMarkAsRead";
    }

    return "";
}

Feedly::Feedly(User& user) :
    m_user(user)
{
}

bool Feedly::IsAvailable()
{
    auto r = cpr::Get(cpr::Url{FeedlyUrl});
    if (r.status_code == 200) {
        return true;
    }

    return false;
}

bool Feedly::Authenticate()
{
    auto r = cpr::Get(cpr::Url{m_rootUrl + "/profile"},
                      cpr::Header{{"Authorization", "OAuth " + m_user.authToken}});

    if (r.status_code == 200) {
        return true;
    }

    return false;
}


map<string, string> Feedly::Categories() const
{
    auto r = cpr::Get(cpr::Url{m_rootUrl + "/categories"},
                      cpr::Header{{"Authorization", "OAuth " + m_user.authToken}});


    if (r.status_code not_eq 200) {
        string error = "Could not get categories: " + to_string(r.status_code);
        throw runtime_error(error.c_str());
    }

    auto jsonResp = json::parse(r.text);

    map<string, string> categories;
    for (auto& ctg : jsonResp) {
        const string label = ctg["label"];
        const string id = ctg["id"];
        categories[label] = id;
    }

    return categories;
}

void Feedly::MarkEntriesWithAction(const vector<string>& entryIds, Actions action)
{
    if (entryIds.size() > 0) {

        json j;
        j["type"] = "entries";

        for (auto& id : entryIds) {
            j["entryIds"].push_back(id);
        }

        j["action"] = ActionToStr(action);

        auto r = cpr::Post(cpr::Url{m_rootUrl + "/markers"},
                           cpr::Body{j.dump()},
                           cpr::Header{{"Authorization", "OAuth " + m_user.authToken},
                                       {"Content-Type", "application/json"}});
        if (r.status_code not_eq 200) {
            string error = "Could not mark entires with " + ActionToStr(action) + ": " + to_string(r.status_code);
            throw runtime_error(error.c_str());
        }
    }
}

void Feedly::MarkCategoryWithAction(const string& categoryId, Actions action, const string& lastReadEntryId)
{
    if (not categoryId.empty()) {
        throw runtime_error("Category ID cannot be empty");
    }

    json j;
    j["type"] = "categories";
    j["categoryIds"] = {categoryId};

    if (not lastReadEntryId.empty()) {
        j["lastReadEntryId"] = lastReadEntryId;
    }
    j["action"] = ActionToStr(action);

    auto r = cpr::Post(cpr::Url{m_rootUrl + "/markers"},
                       cpr::Header{{"Authorization", "OAuth " + m_user.authToken},
                                   {"Content-Type", "application/json"}},
                       cpr::Body{j.dump()});

    if (r.status_code not_eq 200) {
        string error = "Could not mark category with " + ActionToStr(action) + ": " + to_string(r.status_code);
        throw runtime_error(error.c_str());
    }
}

void Feedly::AddSubscription(const string& feed, const string& title, const vector<string> *const categories)
{
    json j;
    j["id"] = "feed/" + feed;
    j["title"] = title;

    if (categories && categories->size() > 0) {
        for (const auto& ctg : *categories) {
            j["categories"].push_back({{"id", ctg}});
        }
    } else {
        j["categories"] = {};
    }

    auto r = cpr::Post(cpr::Url{m_rootUrl + "/subscription"},
                       cpr::Header{{"Authorization", "OAuth " + m_user.authToken}},
                       cpr::Body{j.dump()});

    if (r.status_code not_eq 200) {
        string error = "Could not add subscription: " + to_string(r.status_code);
        throw runtime_error(error.c_str());
    }
}

vector<Feedly::Entry> Feedly::Entries(const string& categoryId, bool sortByOldest, unsigned int count, bool unreadOnly, string continuationId, unsigned long newerThan)
{
    auto params = cpr::Parameters({
            {"ranked",       sortByOldest ? "oldest" : "newest"},
            {"unreadOnly",   unreadOnly ? "true" : "false"},
            {"count",        to_string(count)}
            });

    if (not continuationId.empty()) {
        params.AddParameter(cpr::Parameter{"continuation", continuationId});
    }

    if (newerThan > 0) {
        params.AddParameter(cpr::Parameter{"newerThan", to_string(newerThan)});
    }

    if (categoryId == "All") {
        params.AddParameter(cpr::Parameter{"streamId", "user/" + m_user.id + "/category/global.all"});
    } else if (categoryId == "Uncategorized") {
        params.AddParameter(cpr::Parameter{"streamId", "user/" + m_user.id + "/category/global.uncategorized"});
    } else if (categoryId == "Saved") {
        params.AddParameter(cpr::Parameter{"streamId", "user/" + m_user.id + "/tag/global.saved"});
    } else {
        params.AddParameter(cpr::Parameter{"streamId", categoryId});
    }

    auto r = cpr::Get(cpr::Url{m_rootUrl + "/streams/contents"},
                      cpr::Header{{"Authorization", "OAuth " + m_user.authToken}},
                      params);

    if (r.status_code not_eq 200) {
        string error = "Could not get entries: " + to_string(r.status_code);
        throw runtime_error(error.c_str());
    }

    auto j = json::parse(r.text);

    vector<Feedly::Entry> entries;
    for (auto& item : j["items"]) {
        string title = item["title"];
        string id = item["id"];
        string originID = item["originId"];

        string content;
        if (item["summary"]["content"].is_string()) {
            content = item["summary"]["content"];
        }

        string originTitle;
        if (item["origin"]["title"].is_string()) {
            originTitle = item["origin"]["title"];
        }

        entries.emplace_back(
            content,
            title,
            id,
            originID,
            originTitle
            );
    }

    return entries;
}

/*
   void Feedly::Counts()
   {
   Request req("markers/counts");

   Json::Reader reader;
   Json::Value root;

   map<string, unsigned int>* temp = new map<string, unsigned int>;

   if (root.isMember("unreadcounts") && root["unreadcounts"].isArray()) {
   for (unsigned int i = root["unreadcounts"].size() - user_data.categories.size() + 1;
   i < root["unreadcounts"].size();
   i++)
   {
   (*temp)[root["unreadcounts"][i]["id"].asString()] = root["unreadcounts"][i]["count"].asUInt();
   }
   }

   return temp;

   }
   */
