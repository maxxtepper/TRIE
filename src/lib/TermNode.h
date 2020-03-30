#ifndef TRIE_SRC_LIB_TERMNODE_H_
#define TRIE_SRC_LIB_TERMNODE_H_

#include <memory>
#include <unordered_map>
#include "Node.h"

class TermNode : public Node {
	public:
		TermNode(const char n) : Node(n) {}
		~TermNode() = default;

		virtual bool AddLetters(const std::string &word, uint8_t letter);
		virtual bool TryAddLetters(const std::string &word, uint8_t letter);
		virtual bool TryLetters(const std::string &word, uint8_t letter);

	private:
};

#endif
