#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Trie.h"

TEST(TrieShould, PlaySparseWord){
	//	Global to all tests
	std::shared_ptr<Trie> trie = std::make_shared<Trie>();
	//	Add many words to a word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();
	word_list->push_back("hello");
	word_list->push_back("halo");
	word_list->push_back("helix");
	word_list->push_back("hug");
	word_list->push_back("higg");
	word_list->push_back("helmet");
	word_list->push_back("hi");
	word_list->push_back("pill");
	word_list->push_back("fall");
	word_list->push_back("bye");
	//	Add the words from list
	for (std::string word : *word_list) {
		trie->insert(word);
	}

	//	Test0
	//	Get List and check equal
	std::string sparse_word0 = "h l  ";
	std::unique_ptr<WordList> expected0 = std::make_unique<WordList>();
	expected0->push_back("helix");
	expected0->push_back("hello");
	std::unique_ptr<WordList> actual0 = trie->SparseWord(sparse_word0);
	EXPECT_EQ(*expected0, *actual0);
	
	//	Test1
	//	Get List and check empty 
	std::string sparse_word1 = "h l";
	std::unique_ptr<WordList> word_list_expected1 = std::make_unique<WordList>();
	std::unique_ptr<WordList> expected1 = nullptr;
	std::unique_ptr<WordList> actual1 = trie->SparseWord(sparse_word1);
	EXPECT_EQ(expected1, actual1);

	//	Test2
	//	Get List and check equal
	std::string sparse_word2 = "  ll";
	std::unique_ptr<WordList> expected2 = std::make_unique<WordList>();
	expected2->push_back("fall");
	expected2->push_back("pill");
	std::unique_ptr<WordList> actual2 = trie->SparseWord(sparse_word2);
	EXPECT_EQ(*expected2, *actual2);
} 

TEST(TrieShould, PlaySparsePrefix){
	//	Global to all tests
	std::shared_ptr<Trie> trie = std::make_shared<Trie>();
	//	Add words to trie
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();
	word_list->push_back("hello");
	word_list->push_back("halo");
	word_list->push_back("helix");
	word_list->push_back("hug");
	word_list->push_back("higg");
	word_list->push_back("helmet");
	word_list->push_back("hi");
	word_list->push_back("pill");
	word_list->push_back("fall");
	word_list->push_back("bye");
	for (std::string word : *word_list) {
		trie->insert(word);
	}

	//	Test0
	//	Get List and check equal
	std::string sparse_word0 = "h l";
	std::unique_ptr<WordList> expected0 = std::make_unique<WordList>();
	expected0->push_back("halo");
	expected0->push_back("helix");
	expected0->push_back("hello");
	expected0->push_back("helmet");
	std::unique_ptr<WordList> actual0 = trie->SparsePrefix(sparse_word0);
	EXPECT_EQ(*expected0, *actual0);
	
	//	Test1
	//	Get List and check empty 
	std::string sparse_word1 = "h b";
	std::unique_ptr<WordList> expected1 = nullptr;
	std::unique_ptr<WordList> actual1 = trie->SparsePrefix(sparse_word1);
	EXPECT_EQ(expected1, actual1);

	//	Test2
	//	Get List and check equal
	std::string sparse_word2 = "  l";
	std::unique_ptr<WordList> expected2 = std::make_unique<WordList>();
	expected2->push_back("fall");
	expected2->push_back("halo");
	expected2->push_back("helix");
	expected2->push_back("hello");
	expected2->push_back("helmet");
	expected2->push_back("pill");
	std::unique_ptr<WordList> actual2 = trie->SparsePrefix(sparse_word2);
	EXPECT_EQ(*expected2, *actual2);
}
