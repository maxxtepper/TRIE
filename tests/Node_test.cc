#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Node.h"

TEST(NodeShould, ReturnSomething){
	char expected = 'a';
	std::unique_ptr<Node> node = std::make_unique<Node>(expected);
	char actual = node->GetChar();
	EXPECT_EQ(expected, actual);
}
