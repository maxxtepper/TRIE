#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Trie.h"

TEST(TrieShould, ReturnSomething){
	std::unique_ptr<Trie> trie = std::make_unique<Trie>();
	std::string actual = trie->DoSomething();
	std::string expected = Something;
	EXPECT_EQ(expected, actual);
}
