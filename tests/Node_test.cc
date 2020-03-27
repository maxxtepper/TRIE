#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Node.h"

TEST(NodeShould, ReturnSomething){
	std::unique_ptr<Node> node = std::make_unique<Node>();
	std::string actual = node->DoSomething();
	std::string expected = Something;
	EXPECT_EQ(expected, actual);
}
