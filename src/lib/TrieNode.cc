#include "TrieNode.h"

Trie::Trie() : trie_root_(std::make_unique<TrieNode>('#')) {
}

bool Trie::AddWord(const std::string &word) {
	//	Main method for TRIE building
	//	Loop through each char in the word
	if (word.size() < 1) return false;

	uint8_t letter = 0;
	return (TryAddLetters_(trie_root_, word, letter));
}

bool Trie::TryAddLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter) {
	//	End of word reached
	if (letter == word.size()) { 
		return (AddLetters_(node, word, letter));
	}

	//	Try the letter of the node's child
	if (node.TryChar(letter)) {
			//	The letter is in the tree, traverse
			return (TryAddLetters_(node->child[word[letter]], word, letter++));
	} else {
		//	The letter is not in the tree
		return (AddLetters_(node,word,letter));
	}
}

bool Trie::AddLetters_(std::unique_ptr<Node> &node, const std::string &word, uint8_t letter) {
	//	End of word check
	if (letter == word.size()) { 
		//	Add the terminating character
		std::unique_ptr<TrieNode> child_node = std::make_unique<TrieNode>(letter);
		node->child.insert(std::make_pair('*',child_node));
		return true;
	}

	//	Add the letter
	std::unique_ptr<TrieNode> child_node = std::make_unique<TrieNode>(letter);
	node->child.insert(std::make_pair(word[letter],child_node));

	//	Try the next letter
	if (letter < word.size()) { 
		return (AddLetters_(node,word,letter++));
	//	Add termination to last node
	} else {
		return (AddLetters_(node,word,letter)); }
	}
}

bool Trie::TryWord(const std::string &word) {
	//	Main method for word searching
	if (word.size() < 1) return false;

	std::unique_ptr<TrieNode> node = trie_root_;

	uint8_t letter = 0;
	return (TryLetters_(trie_root_, word, letter));

	if (TryAddLetters_(node, word, word.size()-1))
		return true;
	else return false;
}

bool Trie::TryLetters_(std::unique_ptr<TrieNode> &node, const std::string &word, uint8_t letter) {
	//	End of word reached
	if (word[letter] == '*') { return true; }

	//	Try the letter of the node's child
	if (node->child.count(letter)) {
			//	The letter is in the tree, traverse
			return (TryAddLetters_(node->child[word[letter]], word, letter++));
	} else {
		//	The letter is not in the tree
		return false;
	}
}
virtual char TrieNode::TryChar(char letter) {
	if (child_.count(letter))
		return true;
	else
		return false;
}
