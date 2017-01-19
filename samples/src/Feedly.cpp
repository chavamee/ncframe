#include "api/Feedly.hpp"
// TODO: Merge Response and Request into a single headers
// and a single namespace
#include "api/Response.hpp"
#include "api/Request.hpp"
#include <json/json.h>
#include <fstream>
#include <cassert>

using namespace std;

inline string ActionToStr(Actions action)
{
    switch (action) {
        case READ:
            return "markAsRead";
            break;
        case UNREAD:
            return "undoMarkAsRead";
            break;
        case SAVED:
            return "markAsSaved";
            break;
        case UNSAVED:
            return "markAsUnsaved";
    }

    return "";
}

Feedly::Feedly(User& user) :
    m_user(user)
{
}

bool Feedly::IsAvailable()
{
    Request req("https://feedly.com");
    auto resp = req.Get();

    if (resp.StatusCode() == 200) {
        return true;
    }

    return false;
}

bool Feedly::Authenticate()
{
    Request req(m_rootUrl + "/profile");

    req.SetHeaders({{"Authorization", "OAuth " + m_user.authToken}});

    auto resp = req.Get();

    if (resp.StatusCode() == 200) {
        return true;
    }

    return false;
}


map<string, string> Feedly::Categories() const
{
    Request req(m_rootUrl + "/categories");
    req.SetHeaders({{"Authorization", "OAuth " + m_user.authToken}});
    req.SetOutputFile("output.test");

    auto resp = req.Get();

    if (resp.StatusCode() not_eq 200) {
        string error = "Could not get categories " + to_string(resp.StatusCode());
        throw runtime_error(error.c_str());
    }

    ifstream output("output.test", ifstream::binary);
    Json::Value root;
    Json::CharReaderBuilder rbuilder;
    string errs;

    if (not Json::parseFromStream(rbuilder, output, &root, &errs)) {
        // Report error
    }

    map<string, string> ctgs;

    for (unsigned int i = 0; i < root.size(); i++) {
        ctgs[root[i]["label"].asString()] = root[i]["id"].asString();
    }

    return ctgs;
}

void Feedly::MarkEntriesWithAction(const vector<string>& entryIds, Actions action)
{
    if (entryIds.size() > 0) {

        Json::Value root;
        Json::Value array;

        root["type"] = "entries";

        for (auto& id : entryIds) {
            /*
             * Append returns a reference to the just appended Json::Value
             */
            array.append("entryIds") = id;
        }

        root["entryIds"] = array;
        root["action"] = ActionToStr(action);

        Json::StreamWriterBuilder wbuilder;
        string document = Json::writeString(wbuilder, root);

        Request req(m_rootUrl + "/markers");

        req.SetHeaders({{"Authorization", "OAuth " + m_user.authToken},
                        {"Content-Type", "application/json"}});
        req.SetBody(document);

        auto resp = req.Post();

        if (resp.StatusCode() != 200) {
            // Error msg
        }
    }
}

void Feedly::MarkCategoryWithAction(const string& categoryId, Actions action, const string& lastReadEntryId)
{
    assert(not categoryId.empty());
    //TODO: Probably better to just ignore
    assert(action != SAVED || action != UNSAVED);

    Json::Value root;
    Json::Value array;

    root["type"] = "categories";

    array.append("categoryIds") = categoryId;

    if (not lastReadEntryId.empty()) {
        root["lastReadEntryId"] = lastReadEntryId;
    }
    root["categoryIds"] = array;
    root["action"] = ActionToStr(action);
    root["type"] = "categories";

    Json::StreamWriterBuilder wbuilder;
    string document = Json::writeString(wbuilder, root);

    Request req(m_rootUrl + "/markers");
    req.SetHeaders({{"Authorization", "OAuth " + m_user.authToken},
            {"Content-Type", "application/json"}});
    req.SetBody(document);

    auto resp = req.Post();

    if (resp.StatusCode() != 200) {
        // Error msg
    }
}

void Feedly::AddSubscription(const string& feed, const string& title, const vector<string> *const categories)
{
    Json::Value root;
    root["id"] = "feed/" + feed;
    root["title"] = title;

    if (categories && categories->size() > 0) {
        for (const auto& ctg : *categories) {
            Json::Value idMember;
            idMember["id"] = ctg;
            root["categories"].append(idMember);
        }
    } else {
        root["categories"] = Json::Value(Json::arrayValue);
    }

    Json::StreamWriterBuilder wbuilder;
    string document = Json::writeString(wbuilder, root);

    Request req(m_rootUrl + "/subscriptions");

    req.SetHeaders({{"Authorization", "OAuth " + m_user.authToken}});
    req.SetBody(document);

    auto resp = req.Post();

    if (resp.StatusCode() != 200) {
        // Error msg
    }
}

/*
 * TODO: Figure out what needs to be done to avoid problems when the amount of fetched entries
 * is really big.
 */
vector<Feedly::Entry> Feedly::Entries(const string& categoryId, bool sortByOldest, unsigned int count, bool unreadOnly, string continuationId, unsigned long newerThan)
{
    Request req(m_rootUrl + "/streams/contents");
    Response resp;

    req.SetHeaders({{"Authorization", "OAuth " + m_user.authToken}});
    req.SetOutputFile("test.output");
    req.SetParameters({
            {"ranked",       sortByOldest ? "oldest" : "newest"},
            {"unreadOnly",   unreadOnly ? "true" : "false"},
            {"count",        to_string(count)}
            });

    if (not continuationId.empty()) {
        req.SetParameters({{"continuation", continuationId}});
    }

    if (newerThan > 0) {
        req.SetParameters({{"newerThan", to_string(newerThan)}});
    }

    if (categoryId == "All") {
        req.SetParameters({{"streamId", "user/" + m_user.id + "/category/global.all"}});
    } else if (categoryId == "Uncategorized") {
        req.SetParameters({{"streamId", "user/" + m_user.id + "/category/global.uncategorized"}});
    } else if (categoryId == "Saved") {
        req.SetParameters({{"streamId", "user/" + m_user.id + "/tag/global.saved"}});
    } else {
        req.SetParameters({{"streamId", categoryId}});
    }

    resp = req.Get();

    ifstream output("test.output", ifstream::binary);
    Json::Value root;
    Json::CharReaderBuilder rbuilder;
    string errs;
    if (not Json::parseFromStream(rbuilder, output, &root, &errs)) {
        // Report error
    }

    vector<Feedly::Entry> feeds;

    for (auto& it : root["items"]) {
        feeds.emplace_back(
                it["summary"]["content"].asString(),
                it["title"].asString(),
                it["id"].asString(),
                it["originId"].asString(),
                it["origin"]["title"].asString()
                );
    }

    return feeds;
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
