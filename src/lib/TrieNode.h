#ifndef TRIE_SRC_LIB_TRIENODE_H_
#define TRIE_SRC_LIB_TRIENODE_H_

#include <memory>
#include <unordered_map>
#include "Node.h"

class TrieNode : public Node {
	public:
		TrieNode(char n) : Node(n) {}
		~TrieNode();

		virtual char GetChar();
	private:
		std::unordered_map<char,std::unique_ptr<Node>> child_;
};

#endif
