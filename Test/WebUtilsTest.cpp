#include <gtest/gtest.h>
#include <webserver/WebUtils.h>

TEST(WebUtilsTest, split) {
    auto retVal=webserver::split("hello world how is it going?",' ');
    ASSERT_EQ (retVal.size (),6);
    ASSERT_EQ (retVal [0],"hello");
    ASSERT_EQ (retVal [5],"going?");
}

TEST(WebUtilsTest, split_no_seperator) {
    auto retVal=webserver::split("hello",' ');
    ASSERT_EQ (retVal.size (),1);
    ASSERT_EQ (retVal [0],"hello");
}

TEST(WebUtilsTest, split_double_seperator) {
    auto retVal=webserver::split("hello  world",' ');
    ASSERT_EQ (retVal.size (),2);
    ASSERT_EQ (retVal [0],"hello");
    ASSERT_EQ (retVal [1],"world");
}


