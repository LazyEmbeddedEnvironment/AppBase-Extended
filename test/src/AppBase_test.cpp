//
// Created by jonb on 3/21/19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#define private public
#define protected public

#include <friend/appbase/AppBase.h>

using namespace Friend::AppBase;

class AppBaseTest : public ::testing::Test
{
public:
    unique_ptr<AppBase> base;
    void SetUp() override {
        base = unique_ptr<AppBase>(new AppBase());
    }
    void TearDown() override {

    }
};

TEST_F(AppBaseTest, classCreated) {
    ASSERT_TRUE(base != nullptr);
}