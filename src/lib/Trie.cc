#include "TrieNode.h" 

TrieNode::TrieNode(const char n, const std::string word) : Node(n), word_(word) {
}

bool TrieNode::insert(const std::string &word) {
	//	Main method for TRIE building
	//	Loop through each char in the word
	if (word.size() < 1) return false;

	uint16_t letter = 0;
	return (this->TryAddLetters(word, letter));
}

bool TrieNode::find(const std::string &word) {
	//	Main method for word searching
	if (word.size() < 1) return false;

	uint16_t letter = 0;
	return (this->TryLetters(word, letter));
}

std::unique_ptr<WordList> TrieNode::SparseWord(const std::string &word) {
	//	Main method for sparse word searching
	if (word.size() < 1) return nullptr;

	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	Run the search
	uint16_t letter = 0;
	TrySparseWord(word, letter, word_list);

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

std::unique_ptr<WordList> TrieNode::PrefixList(const std::string &word) {
	//	Traverse every word up to the input substring
	if (word.size() < 1) return nullptr;

	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	Run the search
	uint16_t letter = 0;
	bool list_made = TryPrefix(word, letter, word_list);

	//	Output the result
	if (list_made)
		return (word_list);
	else return nullptr;
}
void TrieNode::PrintChildren() {
	for (auto itr = child_.begin(); itr != child_.end(); ++itr)
		std::cout << itr->first << std::endl;
}

std::unique_ptr<WordList> TrieNode::SparsePrefix(const std::string &word) {
	//	Traverse every word up to the input substring
	if (word.size() < 1) return nullptr;

	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	Run the search
	uint16_t letter = 0;
	TrySparsePrefix(word, letter, word_list);

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

uint64_t TrieNode::node_count_ = 0;

//	Private methods

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
		//	Add the terminating character if the word is not already there
		if (!child_.count('*')) {
			std::unique_ptr<Node> term_node = std::make_unique<TermNode>('*');
			auto letter_ptr_pair = std::make_pair('*', std::move(term_node));
			child_.insert(std::move(letter_ptr_pair));
			return true;
		} else return false;
	}

	//	Add the letter to child
	std::string sub_word;
	for (uint16_t i=0; i<letter+1; i++)
		sub_word.push_back(word[i]);
	std::unique_ptr<Node> child_node = std::make_unique<TrieNode>(word[letter], sub_word);
	auto letter_ptr_pair = std::make_pair(word[letter],std::move(child_node));
	child_.insert(std::move(letter_ptr_pair));

	//	Count this new node
	node_count_++;

	//	Add the next letter
	int temp_letter = letter;
	return (child_[word[temp_letter]]->AddLetters(word,++letter));
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

bool TrieNode::TryPrefix(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	//	Traverse trie until substring found
	if (letter == word.size()-1) {
		if (child_.count(word[letter])) {
			return (child_[word[letter]]->GetWords(word, letter, word_list));
		} else return false;
	}

	//	Traverse trie until substring not found
	if (!child_.count(word[letter])) {
		//	This substring is not in the trie
		return false;
	} else {
		//	Test the next letter
		return (child_[word[letter]]->TryPrefix(word, letter+1, word_list));
	}
}

bool TrieNode::GetWords(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	//	This is going to check for a TrieTerm
	if (child_.count('*')) {
		//	The term is here -> add the word to the list
		word_list->push_back(this->GetWord());
	}

	//	Traverse every child
	for (auto itr = child_.begin(); itr != child_.end(); itr++) {
		itr->second->GetWords(word, ++letter, word_list);
	}

	return true;
}

void TrieNode::TrySparseWord(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	//	End of word reached
	if (letter == word.size()) { 
		if (child_.count('*')) {
			word_list->push_back(this->GetWord());
		}
		return;
	}

	//	Check for a space
	if (word[letter] == ' ') {
		//	space was found -> Traverse all children
		for (auto itr = child_.begin(); itr != child_.end(); itr++) {
			itr->second->TrySparseWord(word, letter+1, word_list);
		}
	} else {
		//	no space -> Try the letter of the node's child
		if (child_.count(word[letter])) {
				//	The letter is in the tree, traverse
				child_[word[letter]]->TrySparseWord(word, letter+1, word_list);
		} else {
			//	The letter is not in the tree
			return;
		}
	}

	return;
}

void TrieNode::TrySparsePrefix(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	//	Traverse trie until substring found
	if (letter == word.size()-1) {
		//	Check for a space
		if (word[letter] == ' ') {
			//	space was found -> Traverse all children
			for (auto itr = child_.begin(); itr != child_.end(); itr++) {
				itr->second->GetWords(word, letter+1, word_list);
			}
		} else {
			if (child_.count(word[letter])) {
				//	The letter is in the tree, traverse
				child_[word[letter]]->GetWords(word, letter, word_list);
			} else {
				//	The letter is not in the tree
				return;
			}
		}
	}

	//	Traverse trie until substring not found
	//	Check for a space
	if (word[letter] == ' ') {
		//	space was found -> Traverse all children
		for (auto itr = child_.begin(); itr != child_.end(); itr++) {
			itr->second->TrySparsePrefix(word, letter+1, word_list);
		}
	} else {
		if (!child_.count(word[letter])) {
			//	This substring is not in the trie
			return;
		} else {
			//	Test the next letter
			child_[word[letter]]->TrySparsePrefix(word, letter+1, word_list);
		}
	}

	return;
}
