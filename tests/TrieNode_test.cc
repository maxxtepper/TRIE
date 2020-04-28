#include <memory>
#include "gtest/gtest.h"
#include "src/lib/TrieNode.h"

TEST(TrieNodeShould, BuildTheTrie){
	//	Create trie with no children
	char expected0 = '#';
	std::unique_ptr<TrieNode> trienode = std::make_unique<TrieNode>(expected0,"");
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
}

TEST(TrieShould, GetWords){
	//	Create trie with no children
	char expected0 = '#';
	std::unique_ptr<TrieNode> trienode = std::make_unique<TrieNode>(expected0,"");
	char actual0 = trienode->GetChar();
	EXPECT_EQ(expected0, actual0);
	
	//	Add words to trie
	std::vector<std::string> words;
	words.push_back("hello");
	words.push_back("hell");
	words.push_back("helix");
	words.push_back("help");
	words.push_back("helm");
	words.push_back("helmet");
	words.push_back("hi");
	words.push_back("bye");
	for (auto itr = words.begin(); itr != words.end(); ++itr) {
		trienode->AddWord(*itr);
	//	std::cout << "Added " << *itr << std::endl;
	}

	//	Test with all the words 
	bool actual1 = true;
	for (auto itr = words.begin(); itr != words.end(); ++itr) {
		if (trienode->TryWord(*itr)) {
//			std::cout << *itr << ": true\n";
		} else {
//			std::cout << *itr << ": false\n";
			actual1 = false;
		}

	}
	bool expected1 = true;
	EXPECT_EQ(expected1, actual1);

	//	Test with all the wrong words 
	std::vector<std::string> wrong_words;
	wrong_words.push_back("angst");
	wrong_words.push_back("helper");
	wrong_words.push_back("helmhelm");
	bool actual2 = false;
	for (auto itr = wrong_words.begin(); itr != wrong_words.end(); ++itr) {
		if (trienode->TryWord(*itr)) {
//			std::cout << *itr << ": true\n";
			actual2 = true;
		} else {
//			std::cout << *itr << ": false\n";
		}

	}
	bool expected2 = false;
	EXPECT_EQ(expected2, actual2);

	//	Get List and check equal
	std::string prefix3 = "hel";
	std::unique_ptr<WordList> word_list_expected3 = std::make_unique<WordList>();
	word_list_expected3->push_back("helix");
	word_list_expected3->push_back("hell");
	word_list_expected3->push_back("hello");
	word_list_expected3->push_back("helm");
	word_list_expected3->push_back("helmet");
	word_list_expected3->push_back("help");

	std::unique_ptr<WordList> word_list_actual3 = trienode->GetList(prefix3);
	bool expected3 = true;
	bool actual3 = std::equal(word_list_expected3->begin(), word_list_expected3->end(), word_list_actual3->begin());
	EXPECT_EQ(expected3, actual3);
	
	//	Get List and check empty 
	std::string prefix4 = "ch";
	std::unique_ptr<WordList> word_list_expected4 = std::make_unique<WordList>();

	std::unique_ptr<WordList> word_list_actual4 = trienode->GetList(prefix4);
	bool expected4 = true;
	bool actual4;
	if (word_list_actual4 == nullptr) actual4 = true;
	else actual4 = false;
	EXPECT_EQ(expected4, actual4);
	
	/*
	*/
}
