#include <memory>
#include "gtest/gtest.h"
#include "src/lib/TrieNode.h"

TEST(TrieNodeShould, ReturnSomething){
	//	Create trie with no children
	char expected0 = '#';
	std::unique_ptr<TrieNode> trienode = std::make_unique<TrieNode>(expected0);
	char actual0 = trienode->GetChar();
	EXPECT_EQ(expected0, actual0);

	//	Check that try letter finds nothing
	int letter = 0;
	std::string word = "";
	bool expected1 = false;
	bool actual1 = trienode->TryLetters(word, letter);
	EXPECT_EQ(expected1, actual1);

	//	Add no letters
	bool expected2 = true;
	bool actual2 = trienode->AddLetters(word, letter);
	EXPECT_EQ(expected2, actual2);
	//	The trie should now have '*' as a child
/*
	//	Try to add a word
	word = "i";
	bool expected3 = true;
	bool actual3 = trienode->AddLetters(word,letter);
	EXPECT_EQ(expected3, actual3);
	*/
}

/*
TEST(TrieNodeAddWord, ReturnAddTrue) {
	char root_char = '#';
	std::unique_ptr<TrieNode> trienode = std::make_unique<TrieNode>(root_char);

	std::string str0 = "word";
	bool expected = trienode->AddWord(str0);
	bool actual = true;
	EXPECT_EQ(expected, actual);
}
*/
