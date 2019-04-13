//
// Created by jonb on 3/21/19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#define private public
#define protected public
#include "../../src/Base.h"

const string name = "someName";
const string expectedName = "int.someName";

class BaseInheritor : public Friend::DDS::Base<int>
{
public:
    bool isConnected() override {};
    using Friend::DDS::Base<int>::Base;
    ~BaseInheritor() { };
};

class MockBaseInheritor : public BaseInheritor
{
public:
    MOCK_METHOD1(create, void(const string& name));
};

class BaseTest : public ::testing::Test
{
public:
    unique_ptr<BaseInheritor> base;
    void SetUp() override {
        base = unique_ptr<BaseInheritor>(new BaseInheritor());
    }
    void TearDown() override {

    }
};

TEST_F(BaseTest, classCreated) {
    ASSERT_TRUE(base != nullptr);
}
TEST_F(BaseTest, setName) {
    base->create(name);
    ASSERT_EQ(expectedName, base->_myName);
}
TEST_F(BaseTest, readLastState) {
    base->_lastState = 42;
    ASSERT_EQ(42, base->read());
}
TEST_F(BaseTest, DISABLED_createClassWithName) {
    unique_ptr<MockBaseInheritor> mockBase;
    EXPECT_CALL(*mockBase, create(expectedName));
    mockBase = unique_ptr<MockBaseInheritor>(new MockBaseInheritor());
}