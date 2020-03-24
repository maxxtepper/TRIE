#ifndef TRIE_SRC_LIB_TRIE_H_
#define TRIE_SRC_LIB_TRIE_H_

#include <string>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <unordered_map>

struct TrieNode {
	std::unordered_map<char,std::shared_ptr<TrieNode>> child;
	char val;
	TrieNode(char x) : val(x) {}
};

class Trie {
	public:
		Trie();
		~Trie();

		void AddWord(const std::string &word);
		bool TryWord(const std::string &word);
		
	private:
		std::shared_ptr<TrieNode> root_;
		void AddLetter_(const std::shared_ptr<TrieNode> node, const char letter);
		bool TryLetter_(const std::shared_ptr<TrieNode> node, const char letter);
		
};

#endif
