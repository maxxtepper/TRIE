#ifndef TRIE_SRC_LIB_NODE_H_
#define TRIE_SRC_LIB_NODE_H_

#include <string>

class Node {
	public:
		Node(const char n) : val_(n) {}
		virtual ~Node() = default;

		char GetChar() { return val_; }

		virtual bool AddLetters(const std::string &word, uint16_t letter) = 0;
		virtual bool TryAddLetters(const std::string &word, uint16_t letter) = 0;
		virtual bool TryLetters(const std::string &word, uint16_t letter) = 0;

	private:
		const char val_;

};

#endif
