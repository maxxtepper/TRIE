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

	//	Try to add an empty word -> it should not
	word = "";
	bool expected3 = false;
	bool actual3 = trienode->AddWord(word);
	EXPECT_EQ(expected3, actual3);

	//	Try to add a letter to the root
	word = "g";
	bool expected4 = true;
	bool actual4 = trienode->AddLetters(word,letter);
	EXPECT_EQ(expected4, actual4);

	//	Try to add letters
	word = "word";
	bool expected5 = true;
	bool actual5 = trienode->AddLetters(word,letter);
	EXPECT_EQ(expected5, actual5);

	//	Try to get that word
	bool expected6 = true; 
	bool actual6 = trienode->TryWord(word);
	EXPECT_EQ(expected6, actual6);

	//	Try to get the wrong word
	word = "farce";
	bool expected7 = false; 
	bool actual7 = trienode->TryWord(word);
	EXPECT_EQ(expected7, actual7);

	//	TryAddLetters on a word
	word = "farce";
	bool expected8 = true; 
	bool actual8 = trienode->TryAddLetters(word,letter);
	EXPECT_EQ(expected8, actual8);

	//	AddWord
	word = "fantastic";
	bool expected9 = true; 
	bool actual9 = trienode->AddWord(word);
	EXPECT_EQ(expected9, actual9);

	//	TryWord
	word = "fantastic";
	bool expected10 = true; 
	bool actual10 = trienode->TryWord(word);
	EXPECT_EQ(expected10, actual10);

	//	TryWord wrong word
	word = "hello";
	bool expected11 = false; 
	bool actual11 = trienode->TryWord(word);
	EXPECT_EQ(expected11, actual11);

	//	Try partially correct word
	word = "fant";
	bool expected12 = false; 
	bool actual12 = trienode->TryWord(word);
	EXPECT_EQ(expected12, actual12);

	//	Add prefix of word
	word = "fant";
	bool expected13 = true; 
	bool actual13 = trienode->AddWord(word);
	EXPECT_EQ(expected13, actual13);

	//	Get count
	uint64_t expected14 = 17; 
	uint64_t actual14 = trienode->Count();
	EXPECT_EQ(expected14, actual14);
	/*
	*/
}
