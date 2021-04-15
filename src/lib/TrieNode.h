#ifndef TRIE_SRC_LIB_TRIENODE_H_
#define TRIE_SRC_LIB_TRIENODE_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Node.h"
#include "TermNode.h"

class TrieNode : public Node {
	public:

		TrieNode(const char n, const std::string word);
		~TrieNode() = default;

		//	Insert word into trie
		bool insert(const std::string &word);

		//	Find word in the trie
		bool find(const std::string &word);

		//	Give a prefix, get a list
		std::unique_ptr<WordList> GetList(const std::string &word);

		//	Object Essentials
		std::string GetWord() { return word_; }
		uint64_t Count() { return node_count_; }
		void PrintChildren();

		//	The node count
		static uint64_t node_count_;

		//	The output words up to this point
		//inline static std::unique_ptr<WordList> word_list_ = std::make_unique<WordList>();
		//static std::unique_ptr<WordList> word_list_;
		
		//	Shared internal methods
		virtual bool TryAddLetters(const std::string &word, uint16_t letter);
		virtual bool AddLetters(const std::string &word, uint16_t letter);
		virtual bool TryLetters(const std::string &word, uint16_t letter);
		virtual bool TryPrefix(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list);
		virtual bool GetWords(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list);

	private:
		//	The children nodes
		std::unordered_map<char,std::unique_ptr<Node>> child_;

		//	The string up to this point
		std::string word_;

};

#endif
