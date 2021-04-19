#ifndef TRIE_SRC_LIB_TRIE_H_
#define TRIE_SRC_LIB_TRIE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include "TrieNode.h"

typedef std::vector<std::string> WordList;

class Trie {
	public:

		Trie();
		~Trie() = default;

		//	Insert word into trie
		bool insert(const std::string &word);

		//	Find word in the trie
		bool find(const std::string &word);
		//	Find sparse word in trie
		std::unique_ptr<WordList> SparseWord(const std::string &word);

		//	Give a prefix, get a list
		std::unique_ptr<WordList> PrefixList(const std::string &word);
		//	Find sparse prefix in trie
		std::unique_ptr<WordList> SparsePrefix(const std::string &word);

		//	Object Essentials
		uint64_t Count() { return node_count_; }
		//void PrintChildren();

		//	The output words up to this point
		//inline static std::unique_ptr<WordList> word_list_ = std::make_unique<WordList>();
		//static std::unique_ptr<WordList> word_list_;
		
	private:
		//	The root node of this trie
		std::shared_ptr<TrieNode> root_;

		//	The node count
		uint64_t node_count_;

		//	End symbol
		char endSymbol_;
};

#endif
