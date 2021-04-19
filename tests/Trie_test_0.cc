#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Trie.h"


TEST(TrieShould, InsertFind){
	//	Global to all tests
	std::shared_ptr<Trie> trie = std::make_shared<Trie>();

	//	Test0
	//	Try to find a word
	std::string word0 = "";
	bool actual0 = false;
	bool expected0 = trie->find(word0);
	EXPECT_EQ(expected0, actual0);

	//	Test1
	//	Add a word
	std::string word1 = "test";
	bool actual1 = true;
	bool expected1 = trie->insert(word1);
	EXPECT_EQ(expected1, actual1);

	//	Test2
	//	Find the word
	std::string word2 = word1;
	bool actual2 = true;
	bool expected2 = trie->find(word2);
	EXPECT_EQ(expected2, actual2);

	//	Test3
	//	Find the wrong word
	std::string word3 = word0;
	bool actual3 = false;
	bool expected3 = trie->find(word3);
	EXPECT_EQ(expected3, actual3);
}

TEST(TrieShould, PrefixList){
	//	Global to all tests
	std::shared_ptr<Trie> trie = std::make_shared<Trie>();
	//	Add many words to a word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();
	word_list->push_back("taste");
	word_list->push_back("tight");
	word_list->push_back("tall");
	word_list->push_back("small");
	word_list->push_back("sick");
	word_list->push_back("sister");

	//	Test0
	//	Add the words from list
	for (std::string word : *word_list) {
		trie->insert(word);
	}
	//	Verify they are there
	bool actual0 = true;
	for (std::string word : *word_list) {
		if (!trie->find(word)) {
			actual0 = false;
			break;
		}
	}
	bool expected0 = true;
	EXPECT_EQ(expected0, actual0);

	//	Test1
	//	Get a list of words from prefix list
	std::string prefix1 = "t";
	std::unique_ptr<WordList> expected1 = std::make_unique<WordList>();
	expected1->push_back("tall");
	expected1->push_back("taste");
	expected1->push_back("tight");
	std::unique_ptr<WordList> actual1 = trie->PrefixList(prefix1);
	EXPECT_EQ(*expected1, *actual1);

	//	Test2
	//	Get a list of words from prefix list
	std::string prefix2 = "si";
	std::unique_ptr<WordList> expected2 = std::make_unique<WordList>();
	expected2->push_back("sick");
	expected2->push_back("sister");
	std::unique_ptr<WordList> actual2 = trie->PrefixList(prefix2);
	EXPECT_EQ(*expected2, *actual2);

	//	Test3
	//	Get a list of words from prefix list
	std::string prefix3 = "b";
	std::unique_ptr<WordList> expected3 = nullptr;
	std::unique_ptr<WordList> actual3 = trie->PrefixList(prefix3);
	EXPECT_EQ(expected3, actual3);
}
