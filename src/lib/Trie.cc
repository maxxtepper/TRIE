#include "Trie.h"

Trie::Trie() {
	root_ = std::make_shared<TrieNode>('#');
}

Trie::~Trie() {
}

void Trie::AddWord(const std::string &word) {
	//	Main method for TRIE building
	//	Loop through each char in the word
	if (word.size() < 1) return;

	std::shared_ptr<TrieNode> node = root_;

	for (unsigned int letter=0; letter<word.size(); letter++) {
		if (TryLetter_(node, word[letter])) {
			//	The letter is in the tree
			node = node->child[word[letter]];
		} else {
			//	The letter is not in the tree
			//	Add this, and all remaining letters
			while (letter < word.size()) {
				AddLetter_(node,word[letter]);
				node = node->child[word[letter]];
				letter++;
			}
			//	Add termination to last node
			AddLetter_(node,'*');
		}
	}
}

bool Trie::TryWord(const std::string &word) {
	//	Main method for word searching
	if (word.size() < 1) return false;

	std::shared_ptr<TrieNode> node = root_;

	unsigned int letter = 0;
	for (letter=0; letter<word.size(); letter++) {
		if (!TryLetter_(node, word[letter]))
			return false;
	}
	
	if (TryLetter_(node, '*'))
		return true;
	else return false;
}

void Trie::AddLetter_(const std::shared_ptr<TrieNode> node, const char letter) {
	std::shared_ptr<TrieNode> new_node = std::make_shared<TrieNode>(letter);
	node->child.insert(std::make_pair(letter,new_node));
}

bool Trie::TryLetter_(const std::shared_ptr<TrieNode> node, const char letter) {
	if (node->child.count(letter))
		return true;
	else return false;
}
