#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Trie.h"

TEST(AddTryShould, AddTry){
	//	Setup object
	std::unique_ptr<Trie> trie = std::make_unique<Trie>();

	//	Add str0
	std::string str0 = "word";
	trie->AddWord(str0);

	//	Try str0
	bool actual0 = trie->TryWord(str0);
	bool expected0 = true;
	EXPECT_EQ(expected0, actual0);
}
