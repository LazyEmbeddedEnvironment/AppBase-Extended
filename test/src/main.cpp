#include <gtest/gtest.h>
#include <ddslinker/Input.h>
#include <memory>

using namespace std;
using namespace Friend::DDS;

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class DDSTest : public ::testing::Test
{
protected:
    unique_ptr<Input<int>> linker;
    virtual void SetUp() override {
        linker = unique_ptr<Input<int>>(new Input<int>());
    }
    virtual void TearDown() override {

    }
};

TEST_F(DDSTest, classCreated) {
    ASSERT_TRUE(linker != nullptr);
}
