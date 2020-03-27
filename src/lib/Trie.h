#ifndef TRIE_SRC_LIB_TRIE_H_
#define TRIE_SRC_LIB_TRIE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include "Node.h"
#include "Root.h"
#include "Child.h"
#include "Term.h"

class Trie {
	public:
		Trie();
		~Trie() = default;

		bool AddWord(const std::string &word);
		bool TryWord(const std::string &word);
		
	private:
		//	This is the root node pointer to the trie
		std::unique_ptr<Root> trie_root_;

		std::unique_ptr<Node> AddLetters_(std::unique_ptr<Node> node, const std::string &word, uint8_t letter);
		std::unique_ptr<Node> TryAddLetters_(std::unique_ptr<Node> node, const std::string &word, uint8_t letter);
		std::unique_ptr<Node> TryLetters_(std::unique_ptr<Node> node, const std::string &word, uint8_t letter);

};

#endif
