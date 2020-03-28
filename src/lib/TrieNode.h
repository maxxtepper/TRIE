#ifndef TRIE_SRC_LIB_TRIENODE_H_
#define TRIE_SRC_LIB_TRIENODE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include "Node.h"
#include "TermNode.h"

class TrieNode : public Node {
	public:
		TrieNode(const char n) : Node(n) {}
		~TrieNode() = default;

		bool AddWord(const std::string &word);
		bool TryWord(const std::string &word);

	private:
		std::unordered_map<char,std::unique_ptr<Node>> child_;

		bool AddLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter);
		bool TryAddLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter);
		bool TryLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter);
};

#endif
