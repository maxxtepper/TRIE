#include <memory>
#include "gtest/gtest.h"
#include "src/lib/TrieNode.h"

TEST(TrieNodeShould, PlaySparseWord){
	//	Create trie
	std::unique_ptr<TrieNode> trienode = std::make_unique<TrieNode>('*',"");
	//	Add words to trie
	std::vector<std::string> words;
	words.push_back("hello");
	words.push_back("halo");
	words.push_back("helix");
	words.push_back("hug");
	words.push_back("higg");
	words.push_back("helmet");
	words.push_back("hi");
	words.push_back("pill");
	words.push_back("fall");
	words.push_back("bye");
	for (auto itr = words.begin(); itr != words.end(); ++itr) {
		trienode->insert(*itr);
	//	std::cout << "Added " << *itr << std::endl;
	}

	//	Get List and check equal
	std::string sparse_word0 = "h l  ";
	std::unique_ptr<WordList> word_list_expected0 = std::make_unique<WordList>();
	word_list_expected0->push_back("helix");
	word_list_expected0->push_back("hello");

	std::unique_ptr<WordList> word_list_actual0 = trienode->SparseWord(sparse_word0);
	for (auto itr = word_list_actual0->begin(); itr != word_list_actual0->end(); ++itr) {
			std::cout << *itr << std::endl;
	}
	bool expected0 = true;
	bool actual0 = std::equal(word_list_expected0->begin(), word_list_expected0->end(), word_list_actual0->begin());
	EXPECT_EQ(expected0, actual0);
	
	//	Get List and check empty 
	std::string sparse_word1 = "h l";
	std::unique_ptr<WordList> word_list_expected1 = std::make_unique<WordList>();

	std::unique_ptr<WordList> word_list_actual1 = trienode->SparseWord(sparse_word1);
	bool expected1 = true;
	bool actual1;
	if (word_list_actual1 == nullptr) actual1 = true;
	else actual1 = false;
	EXPECT_EQ(expected1, actual1);

	//	Get List and check equal
	std::string sparse_word2 = "  ll";
	std::unique_ptr<WordList> word_list_expected2 = std::make_unique<WordList>();
	word_list_expected2->push_back("fall");
	word_list_expected2->push_back("pill");

	std::unique_ptr<WordList> word_list_actual2 = trienode->SparseWord(sparse_word2);
	bool expected2 = true;
	bool actual2 = std::equal(word_list_expected2->begin(), word_list_expected2->end(), word_list_actual2->begin());
	EXPECT_EQ(expected2, actual2);
}

/*
TEST(TrieNodeShould, PlaySparePrefix){
	//	Create trie
	std::unique_ptr<TrieNode> trienode = std::make_unique<TrieNode>('*',"");
	//	Add words to trie
	std::vector<std::string> words;
	words.push_back("hello");
	words.push_back("halo");
	words.push_back("helix");
	words.push_back("hug");
	words.push_back("higg");
	words.push_back("helmet");
	words.push_back("hi");
	words.push_back("pill");
	words.push_back("fall");
	words.push_back("bye");
	for (auto itr = words.begin(); itr != words.end(); ++itr) {
		trienode->insert(*itr);
	//	std::cout << "Added " << *itr << std::endl;
	}

	//	Get List and check equal
	std::string sparse_word0 = "h l";
	std::unique_ptr<WordList> word_list_expected0 = std::make_unique<WordList>();
	word_list_expected0->push_back("hello");
	word_list_expected0->push_back("halo");
	word_list_expected0->push_back("helix");
	word_list_expected0->push_back("helmet");

	std::unique_ptr<WordList> word_list_actual0 = trienode->SparseWord(sparse_word0);
	bool expected0 = true;
	bool actual0 = std::equal(word_list_expected0->begin(), word_list_expected0->end(), word_list_actual0->begin());
	EXPECT_EQ(expected0, actual0);
	
	//	Get List and check empty 
	std::string sparse_word1 = "h b";
	std::unique_ptr<WordList> word_list_expected1 = std::make_unique<WordList>();

	std::unique_ptr<WordList> word_list_actual1 = trienode->SparseWord(sparse_word1);
	bool expected1 = true;
	bool actual1;
	if (word_list_actual1 == nullptr) actual1 = true;
	else actual1 = false;
	EXPECT_EQ(expected1, actual1);

	//	Get List and check equal
	std::string sparse_word2 = "  l";
	std::unique_ptr<WordList> word_list_expected2 = std::make_unique<WordList>();
	word_list_expected2->push_back("hello");
	word_list_expected2->push_back("halo");
	word_list_expected2->push_back("helix");
	word_list_expected2->push_back("helmet");
	word_list_expected2->push_back("pill");
	word_list_expected2->push_back("fall");

	std::unique_ptr<WordList> word_list_actual2 = trienode->SparseWord(sparse_word2);
	bool expected2 = true;
	bool actual2 = std::equal(word_list_expected2->begin(), word_list_expected2->end(), word_list_actual2->begin());
	EXPECT_EQ(expected2, actual2);
}
	*/
