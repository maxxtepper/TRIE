#ifndef TRIE_SRC_LIB_TRIE_H_
#define TRIE_SRC_LIB_TRIE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <unordered_map>

struct TrieNode {
	std::unordered_map<char,std::unique_ptr<TrieNode>> child;
	char val;
	TrieNode(char x) : val(x) {}
	~TrieNode() = default;
};

class Trie {
	public:
		Trie();
		~Trie() = default;

		std::unique_ptr<TrieNode> AddWord(const std::string &word);
		std::unique_ptr<TrieNode> TryWord(const std::string &word);
		
	private:
		//	This is the root unique node pointer to the trie
		std::unique_ptr<TrieNode> root_;

		std::unique_ptr<TrieNode> AddLetters_(std::unique_ptr<TrieNode> node, const std::string &word, uint8_t letter);
		std::unique_ptr<TrieNode> TryAddLetters_(std::unique_ptr<TrieNode> node, const std::string &word, uint8_t letter);
		std::unique_ptr<TrieNode> TryLetters_(std::unique_ptr<TrieNode> node, const std::string &word, uint8_t letter);

};

#endif
