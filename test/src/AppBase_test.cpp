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

class MockAppBase : public AppBase {
public:
    MOCK_METHOD1(setInstance, void(const int &instance));
};

class AppBaseTest : public ::testing::Test {
public:
    unique_ptr<AppBase> base;
    unique_ptr<MockAppBase> mockedBase;
    void SetUp() override {
        base = unique_ptr<AppBase>(new AppBase());
        mockedBase = unique_ptr<MockAppBase>(new MockAppBase());
    }
    void TearDown() override {
        base.reset();
        mockedBase.reset();
    }
};

TEST_F(AppBaseTest, classCreated) {
    ASSERT_TRUE(base != nullptr);
}
TEST_F(AppBaseTest, setInstance) {
    base->setInstance(42);
    ASSERT_EQ(42, base->getInstance());
}
TEST_F(AppBaseTest, pluginInitializeSetsInstance) {
    EXPECT_CALL(*mockedBase, setInstance(testing::_)).Times(1);
    bpo::variables_map vm;
    vm.insert(std::make_pair("instance", bpo::variable_value(32,true)));
    mockedBase->plugin_initialize(vm);
}
TEST_F(AppBaseTest, CMAKE_PROJECT_NAME_toSource) {
    ASSERT_EQ("libfriendappbase", base->getAppName());
}
