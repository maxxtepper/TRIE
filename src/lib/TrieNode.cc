#include "TrieNode.h"

bool Trie::AddWord(const std::string &word) {
	//	Main method for TRIE building
	//	Loop through each char in the word
	if (word.size() < 1) return false;

	uint8_t letter = 0;
	return (TryAddLetters_(this, word, letter));
}

bool Trie::TryAddLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter) {
	//	End of word reached
	if (letter == word.size()) { 
		return (AddLetters_(node, word, letter));
	}

	//	Try the letter of the node's child
	if (child_->count(letter)) {
			//	The letter is in the tree, traverse
			return (TryAddLetters_(child_[letter], word, letter++));
	} else {
		//	The letter is not in the tree
		return (AddLetters_(node,word,letter));
	}
}

bool Trie::AddLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter) {
	//	End of word check
	if (letter == word.size()) { 
		//	Add the terminating character
		std::unique_ptr<Node> term_node = std::make_unique<TermNode>('*');
		child_->insert(std::make_pair('*',term_node));
		return true;
	}

	//	Add the letter
	std::unique_ptr<Node> child_node = std::make_unique<TrieNode>(letter);
	child_->insert(std::make_pair(word[letter],child_node));

	//	Add the next letter
	return (AddLetters_(child_node,word,letter++));
}

bool Trie::TryWord(const std::string &word) {
	//	Main method for word searching
	if (word.size() < 1) return false;

	uint8_t letter = 0;
	return (TryLetters_(this, word, letter));
}

bool Trie::TryLetters_(std::unique_ptr<TrieNode> &node, const std::string &word, uint8_t letter) {
	//	End of word reached
	if (word[letter] == '*') { return true; }

	//	Try the letter of the node's child
	if (child_->count(letter)) {
			//	The letter is in the tree, traverse
			return (TryLetters_(child_[letter], word, letter++));
	} else {
		//	The letter is not in the tree
		return false;
	}
}
