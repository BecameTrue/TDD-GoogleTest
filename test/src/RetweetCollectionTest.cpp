#include "gmock/gmock.h"
#include "RetweetCollection.h"

using namespace ::testing;

class ARetweetCollection: public Test {
public:
    RetweetCollection collection;
};


class ARetweetCollectionWithOneTweet: public Test {
public:
    RetweetCollection collection;
    Tweet* tweet;

    void SetUp() override {
        tweet = new Tweet("msg", "@user");
        collection.add(*tweet);
    }

    void TearDown() override {
        delete tweet;
        tweet = nullptr;
    }
};


TEST_F(ARetweetCollectionWithOneTweet, IsNoLongerEmpty) {
    ASSERT_FALSE(collection.isEmpty());
}

TEST_F(ARetweetCollectionWithOneTweet, HasSizeOfOne) {
    ASSERT_THAT(collection.size(), Eq(1u));
}

TEST_F(ARetweetCollection, IgnoresDuplicateTweetAdded) {
    Tweet duplicate(*tweet);
    collection.add(duplicate);
    collection.add(tweet);
    collection.add(duplicate);

    ASSERT_THAT(collection.size(), Eq(1u));
}
