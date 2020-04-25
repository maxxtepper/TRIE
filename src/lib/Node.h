#ifndef TRIE_SRC_LIB_NODE_H_
#define TRIE_SRC_LIB_NODE_H_

#include <string>

class Node {
	public:
		Node(const char n) : val_(n) {}
		virtual ~Node() = default;

		char GetChar() { return val_; }

		//	Add word to trie
		virtual bool TryAddLetters(const std::string &word, uint16_t letter) = 0;
		virtual bool AddLetters(const std::string &word, uint16_t letter) = 0;

		//	Try the trie
		virtual bool TryLetters(const std::string &word, uint16_t letter) = 0;

		//	Give a prefix, get a list
		virtual bool TryPrefix(const std::string &word, uint16_t letter) = 0;
		virtual bool GetWords(const std::string &word, uint16_t letter) = 0;

	private:
		const char val_;

};

#endif
