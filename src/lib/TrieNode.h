#ifndef TRIE_SRC_LIB_TRIENODE_H_
#define TRIE_SRC_LIB_TRIENODE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include "Node.h"
#include "TermNode.h"

typedef std::unique_ptr<std::vector<std::string>> WordList;

class TrieNode : public Node {
	public:

		TrieNode(const char n);
		~TrieNode() = default;

		//	Add word to trie
		bool AddWord(const std::string &word);
		virtual bool TryAddLetters(const std::string &word, uint16_t letter);
		virtual bool AddLetters(const std::string &word, uint16_t letter);

		//	Try the trie
		bool TryWord(const std::string &word);
		virtual bool TryLetters(const std::string &word, uint16_t letter);

		//	Give a prefix, get a list
		WordList GetList(const std::string &word);
		virtual bool TryPrefix(const std::string &word, uint16_t letter);
		virtual bool GetWords(const std::string &word, uint16_t letter);

		//	Object Essentials
		std::string GetWord() { return word_; }
		uint64_t Count() { return node_count_; }
		void PrintChildren();

		//	The node count
		static uint64_t node_count_;

		//	The output words up to this point
		static WordList word_list_;

	private:
		//	The children nodes
		std::map<char,std::unique_ptr<Node>> child_;

		//	The string up to this point
		std::string word_;
};

#endif
