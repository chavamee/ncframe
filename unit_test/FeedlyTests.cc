#include "gtest/gtest.h"
#include "Feedly.h"
#include <algorithm>

class FeedlyTest : public ::testing::Test {
    protected:
        virtual void SetUp()
        {
        }
};

TEST_F(FeedlyTest, APITest)
{

    Feedly::User user = {"aedcbd40-11cb-49cc-b116-ddc60648d818", "A3M9nq6hGosO2SjVkqqKnKNI4DFYfzc4kjcpsk0DjsY_lepEYd7jbYJ-jxXz8IyZ9DvKIyxoEZGnXeFlhTMDstT8ToU-EFFCpESYZQia3iXHK1373IgtDC9wUAR1F9av928XgAmjrQIFv3EBbf7npZ32abtXfvys0lZM_rFvntb-FxTWNU_0jQTTxAfdz9iZWyoFZiynNDPhnruhYdQuFVR751YQCPM:feedlydev", "", "", "", "", ""};
    Feedly feedly(user);

    try {
        ASSERT_TRUE(feedly.IsAvailable());
        ASSERT_TRUE(feedly.Authenticate());
    } catch (std::exception& e) {
        FAIL();
    }

    auto ctgs = feedly.Categories();

    EXPECT_GT(0, ctgs.size());
    for (auto& it: ctgs) {
        std::cout << it.first << std::endl;
    }

    std::vector<std::string> ids;
    std::transform(ctgs.begin(), ctgs.end(), back_inserter(ids), [](const std::map<std::string, std::string>::value_type& val){return val.second;} );

    EXPECT_NO_THROW(feedly.AddSubscription("http://feeds.feedburner.com/design-milk", "Design Milk", &ids));

    std::vector<Feedly::Entry> entries = feedly.Posts("All");

    EXPECT_GT(0, entries.size());
    for (auto& entry : entries) {
        std::cout << entry.title << std::endl;
    }

    EXPECT_NO_THROW(feedly.MarkPostsWithAction({entries[0].id}, READ));

    std::vector<Feedly::Entry> oldEntries = feedly.Posts("All");

    EXPECT_GT(0, oldEntries.size());
    EXPECT_GT(entries.size(), oldEntries.size());
    for (auto& entry : entries) {
        std::cout << entry.title << std::endl;
    }
}

