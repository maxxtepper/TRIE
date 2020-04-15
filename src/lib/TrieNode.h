#ifndef TRIE_SRC_LIB_TRIENODE_H_
#define TRIE_SRC_LIB_TRIENODE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>
#include <unordered_map>
#include "Node.h"
#include "TermNode.h"

class TrieNode : public Node {
	public:
		TrieNode(const char n) : Node(n) {}
		~TrieNode() = default;

		bool AddWord(const std::string &word);
		bool TryWord(const std::string &word);

		virtual bool AddLetters(const std::string &word, uint16_t letter);
		virtual bool TryAddLetters(const std::string &word, uint16_t letter);
		virtual bool TryLetters(const std::string &word, uint16_t letter);

	private:
		std::unordered_map<char,std::unique_ptr<Node>> child_;
};

#endif
