#include <memory>
#include "gtest/gtest.h"
#include "src/lib/Trie.h"

TEST(TrieShould, SparseEntry){
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
	word_list->push_back("stall");
	word_list->push_back("fall");
	word_list->push_back("bye");
	word_list->push_back("big");
	word_list->push_back("crawl");
	word_list->push_back("able");
	for (std::string word : *word_list) {
		trie->insert(word);
	}

	//	Test0
	//	Get List and check equal
	std::string sparse_word0 = "l";
	std::unique_ptr<WordList> expected0 = std::make_unique<WordList>();
	expected0->push_back("able");
	expected0->push_back("crawl");
	expected0->push_back("fall");
	expected0->push_back("halo");
	expected0->push_back("helix");
	expected0->push_back("hello");
	expected0->push_back("helmet");
	expected0->push_back("pill");
	expected0->push_back("stall");
	std::unique_ptr<WordList> actual0 = trie->SparseEntry(sparse_word0);
	EXPECT_EQ(*expected0, *actual0);

	//	Test1
	//	Get List and check empty 
	std::string sparse_word1 = "z l";
	std::unique_ptr<WordList> expected1 = nullptr;
	std::unique_ptr<WordList> actual1 = trie->SparseEntry(sparse_word1);
	EXPECT_EQ(expected1, actual1);

	//	Test2
	//	Get List and check equal
	std::string sparse_word2 = "ig";
	std::unique_ptr<WordList> expected2 = std::make_unique<WordList>();
	expected2->push_back("big");
	expected2->push_back("higg");
	std::unique_ptr<WordList> actual2 = trie->SparseEntry(sparse_word2);
	EXPECT_EQ(*expected2, *actual2);
}
