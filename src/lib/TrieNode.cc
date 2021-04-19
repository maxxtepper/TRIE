#include "TrieNode.h"

TrieNode::TrieNode(const char letter, const std::string word) {
	letter_ = letter;
	word_ = word;
}

TrieNode::~TrieNode() {
}
