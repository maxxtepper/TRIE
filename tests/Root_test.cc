#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Root.h"

TEST(RootShould, ReturnSomething){
	std::unique_ptr<Root> root = std::make_unique<Root>();
	std::string actual = root->DoSomething();
	std::string expected = Something;
	EXPECT_EQ(expected, actual);
}
