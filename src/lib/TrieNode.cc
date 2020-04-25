#include "TrieNode.h" 

TrieNode::TrieNode(const char n) : Node(n), word_("") {
	//	Create word list
	word_list_ = std::make_unique<std::vector<std::string>>();
}

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
		//	Add the letters up to this point to the word
		if (word_ != word)
			for (uint16_t i=0; i<letter; i++)
				word_.push_back(word[i]);
		return true;
	}

	//	Add the letter to child
	std::unique_ptr<Node> child_node = std::make_unique<TrieNode>(word[letter]);
	auto letter_ptr_pair = std::make_pair(word[letter],std::move(child_node));
	child_.insert(std::move(letter_ptr_pair));
	//	Add the letters up to this point to the word
	for (uint16_t i=0; i<letter; i++)
		word_.push_back(word[i]);
	//	Count this new node
	node_count_++;

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

WordList TrieNode::GetList(const std::string &word) {
	//	Traverse every word up to the input substring
	if (word.size() < 1) return nullptr;

	//	Run the search
	uint16_t letter = 0;
	bool list_made = TryPrefix(word, letter);

	//	Output the result
	if (list_made)
		return std::move(word_list_);
	else return nullptr;
}

bool TrieNode::TryPrefix(const std::string &word, uint16_t letter) {
	std::cout << "Letter: " << letter << "; Word: " << word << std::endl;
	this->PrintChildren();
	//	Traverse trie until substring found
	if (letter == word.size()-1) {
		if (child_.count(word[letter])) {
			std::cout << "Gonna get words for " << word << std::endl;
			return (child_[word[letter]]->GetWords(word, letter));
		} else return false;
	}

	//	Traverse trie until substring not found
	if (!child_.count(word[letter])) {
		//	This substring is not in the trie
		return false;
	} else {
		//	Test the next letter
		uint16_t letter_new = letter++;
		return (child_[word[letter]]->TryPrefix(word, letter_new));
	}
}

bool TrieNode::GetWords(const std::string &word, uint16_t letter) {
	//	Get the iter
	auto itr = child_.begin();

	std::cout << "Gonna iterate for " << word << std::endl;
	//	This is going to check every node for a TrieTerm
	if (itr->first == '*') {
		//	The term is here -> add the word to the list
		std::cout << "Adding word " << this->GetWord() << std::endl;
		word_list_->push_back(this->GetWord());
	}
	itr++;

	//	Traverse every child
	for (; itr != child_.end(); itr++)
		itr->second->GetWords(word, ++letter);

	return true;
}

void TrieNode::PrintChildren() {
	for (auto itr = child_.begin(); itr != child_.end(); ++itr)
		std::cout << itr->first << std::endl;
}

uint64_t TrieNode::node_count_ = 0;
