#include "TrieNode.h" 
bool TrieNode::AddWord(const std::string &word) {
	//	Main method for TRIE building
	//	Loop through each char in the word
	if (word.size() < 1) return false;

	uint16_t letter = 0;
	return (this->TryAddLetters(word, letter));
}

bool TrieNode::TryAddLetters(const std::string &word, uint16_t letter) {
	//	End of word reached
	if (letter == word.size()) { 
		//	Case of adding a word that already has all its letters in the trie
		auto itr = child_.find('*');
		if (itr == child_.end()) {
			std::unique_ptr<Node> term_node = std::make_unique<TermNode>('*');
			auto letter_ptr_pair = std::make_pair('*', std::move(term_node));
			child_.insert(std::move(letter_ptr_pair));
			return true;
		}
		//	This means the word could not be added
		else return false;
	}

	//	Try the letter of the node's child
	auto itr = child_.find(word[letter]);
	if (itr != child_.end()) {
			//	The letter is in the tree, traverse
			int temp_letter = letter;
			return (child_[word[temp_letter]]->TryAddLetters(word, ++letter));
	} else {
		//	The letter is not in the tree
		return (this->AddLetters(word,letter));
	}
}

bool TrieNode::AddLetters(const std::string &word, uint16_t letter) {
	//	End of word check
	if (letter == word.size()) { 
		//	Add the terminating character
		std::unique_ptr<Node> term_node = std::make_unique<TermNode>('*');
		auto letter_ptr_pair = std::make_pair('*', std::move(term_node));
		child_.insert(std::move(letter_ptr_pair));
		return true;
	}

	//	Add the letter
	std::unique_ptr<Node> child_node = std::make_unique<TrieNode>(word[letter]);
	auto letter_ptr_pair = std::make_pair(word[letter],std::move(child_node));
	child_.insert(std::move(letter_ptr_pair));
	node_count++;

	//	Add the next letter
	int temp_letter = letter;
	return (child_[word[temp_letter]]->AddLetters(word,++letter));
}

bool TrieNode::TryWord(const std::string &word) {
	//	Main method for word searching
	if (word.size() < 1) return false;

	uint16_t letter = 0;
	return (this->TryLetters(word, letter));
}

bool TrieNode::TryLetters(const std::string &word, uint16_t letter) {
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
			return (child_[word[temp_letter]]->TryLetters(word, ++letter));
	} else {
		//	The letter is not in the tree
		return false;
	}
}

uint64_t TrieNode::node_count = 0;
