#ifndef TRIE_SRC_LIB_TRIENODE_H_
#define TRIE_SRC_LIB_TRIENODE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

typedef std::vector<std::string> WordList;

class TrieNode {
	public:
		TrieNode(const char letter, const std::string word);
		~TrieNode();

		//	The children nodes
		std::map<char, std::shared_ptr<TrieNode>> children;

		//	Object Essentials
		char GetLetter() { return letter_; }
		std::string GetWord() { return word_; }

	private:
		//	The char of this node
		char letter_;
		//	The word up to this point
		std::string word_;
};

#endif
