#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Child.h"

TEST(ChildShould, ReturnSomething){
	std::unique_ptr<Child> child = std::make_unique<Child>();
	std::string actual = child->DoSomething();
	std::string expected = Something;
	EXPECT_EQ(expected, actual);
}
