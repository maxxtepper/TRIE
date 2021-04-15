#ifndef TRIE_SRC_LIB_TERMNODE_H_
#define TRIE_SRC_LIB_TERMNODE_H_

#include <memory>
#include <unordered_map>
#include "Node.h"

class TermNode : public Node {
	public:
		TermNode(const char n) : Node(n) {}
		~TermNode() = default;

	protected:
		//	Add word to trie
		virtual bool TryAddLetters(const std::string &word, uint16_t letter);
		virtual bool AddLetters(const std::string &word, uint16_t letter);

		//	Try the trie
		virtual bool TryLetters(const std::string &word, uint16_t letter);

		//	Give a prefix, get a list
		virtual bool TryPrefix(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list);
		virtual bool GetWords(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list);

	private:

};

#endif
