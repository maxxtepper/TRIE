#include "TrieNode.h" 
bool TrieNode::AddWord(const std::string &word) {
	//	Main method for TRIE building
	//	Loop through each char in the word
	if (word.size() < 1) return false;

	uint8_t letter = 0;
	return (this->TryAddLetters(word, letter));
}

bool TrieNode::TryAddLetters(const std::string &word, uint8_t letter) {
	//	End of word reached
	if (letter == word.size()) { 
		//	This means the word could not be added
		return false;
	}

	//	Try the letter of the node's child
	if (child_.count(letter)) {
			//	The letter is in the tree, traverse
			int temp_letter = letter;
			return (child_[temp_letter]->TryAddLetters(word, letter++));
	} else {
		//	The letter is not in the tree
		return (child_[letter]->AddLetters(word,letter));
	}
}

bool TrieNode::AddLetters(const std::string &word, uint8_t letter) {
	//	End of word check
	if (letter == word.size()) { 
		//	Add the terminating character
		std::unique_ptr<Node> term_node = std::make_unique<TermNode>('*');
		child_.insert(std::make_pair('*',std::move(term_node)));
		return true;
	}

	//	Add the letter
	std::unique_ptr<Node> child_node = std::make_unique<TrieNode>(word[letter]);
	child_.insert(std::make_pair(word[letter],std::move(child_node)));

	//	Add the next letter
	int temp_letter = letter;
	return (child_[word[temp_letter]]->AddLetters(word,letter++));
}

bool TrieNode::TryWord(const std::string &word) {
	//	Main method for word searching
	if (word.size() < 1) return false;

	uint8_t letter = 0;
	return (this->TryLetters(word, letter));
}

bool TrieNode::TryLetters(const std::string &word, uint8_t letter) {
	//	End of word reached
	if (letter == word.size()) { 
		if (child_.count('*'))
			return true;
		else return false;
	}

	//	Try the letter of the node's child
	if (child_.count(word[letter])) {
			//	The letter is in the tree, traverse
			int temp_letter = letter;
			return (child_[temp_letter]->TryLetters(word, letter++));
	} else {
		//	The letter is not in the tree
		return false;
	}
}
