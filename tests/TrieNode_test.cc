#include <memory>
#include "gtest/gtest.h"
#include "src/lib/TrieNode.h"

//	Global to all tests
char root_letter = '#';
std::string root_word = "";
std::shared_ptr<TrieNode> root = std::make_shared<TrieNode>(root_letter, root_word);

TEST(TrieNodeShould, Construct){
	//	Test0
	//	Get the letter
	char actual0 = root->GetLetter();
	char expected0 = root_letter;
	EXPECT_EQ(expected0, actual0);

	//	Test1
	//	Get the word
	std::string actual1 = root->GetWord();
	std::string expected1 = root_word;
	EXPECT_EQ(expected1, actual1);
}

TEST(TrieNodeShould, AddingNodesFromWord){
	//	Test0
	//	Try to add a letter to the root
	std::shared_ptr<TrieNode> current = root;
	char letter0 = 'g';
	std::string word = "gear";
	std::string subword = "g";

	std::shared_ptr<TrieNode> trie_node = std::make_shared<TrieNode>(letter0, subword);
	auto letter_ptr_pair = std::make_pair(letter0, trie_node);
	current->children.insert(std::move(letter_ptr_pair));
			
	std::shared_ptr<TrieNode> expected0 = trie_node;
	std::shared_ptr<TrieNode> actual0 = current->children[letter0];
	EXPECT_EQ(expected0, actual0);

	//	Test1
	//	Try to add the next letter to that new node
	current = current->children[letter0];
	char letter1 = 'e';
	subword.push_back(letter1);

	trie_node = std::make_shared<TrieNode>(letter1, subword);
	letter_ptr_pair = std::make_pair(letter1, trie_node);
	current->children.insert(std::move(letter_ptr_pair));

	std::shared_ptr<TrieNode> expected1 = trie_node;
	std::shared_ptr<TrieNode> actual1 = current->children[letter1];
	EXPECT_EQ(expected1, actual1);
}

TEST(TrieNodeShould, CheckTheRootNode){
	//	Test0
	//	Try to add a letter to the root
	char expected0 = 'g';
	char actual0 = root->children['g']->GetLetter();
	EXPECT_EQ(expected0, actual0);
}
