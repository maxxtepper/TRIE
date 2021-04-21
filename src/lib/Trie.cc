#include "Trie.h" 

Trie::Trie() {
	std::shared_ptr<TrieNode> trie_node = std::make_shared<TrieNode>('#', "");
	this->root_ = trie_node;
	this->endSymbol_ = '*';
	this->node_count_ = 0;
}

bool Trie::insert(const std::string &word) {
	//	Bad input
	if (word.size() < 1) return false;

	//	Start at the root
	std::shared_ptr<TrieNode> current = this->root_;
	//	Generate the subword
	std::string subword;
	//	Loop down until the whole word is in the trie
	for (char letter : word) {
		//	Add the letter to the subword
		subword.push_back(letter);
		//	See if this letter already exists in this node
		if (!current->children.count(letter)) {
			//	The letter was not found; add a new node
			std::shared_ptr<TrieNode> trie_node = std::make_shared<TrieNode>(letter, subword);
			auto letter_ptr_pair = std::make_pair(letter, trie_node);
			//	Put it in the trie
			current->children.insert(letter_ptr_pair);
			//	Put it in the level list
			this->node_char_list_.insert(letter_ptr_pair);
			node_count_++;
		}
		//	Go to next node
		current = current->children[letter];
	}

	//	Insert the termination
	current->children.insert({this->endSymbol_, nullptr});

	return true;
}

bool Trie::find(const std::string &word) {
	//	Bad input
	if (word.size() < 1) return false;

	//	Start at the root
	std::shared_ptr<TrieNode> current = this->root_;

	//	Loop down until the whole word is found or something is not found
	for (char letter : word) {
		//	See if this letter exists in this node
		if (!current->children.count(letter)) {
			//	Not found
			return false;
		}
		//	Go to next node
		current = current->children[letter];
	}

	//	At the end of word, check for termination
	if (!current->children.count(endSymbol_))
		return false;
	else
		return true;
}

std::unique_ptr<WordList> Trie::SparseWord(const std::string &word) {
	//	Main method for sparse word searching
	if (word.size() < 1) return nullptr;

	//	The word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	The Depth-Level Queue to process
	std::queue<std::shared_ptr<TrieNode>> current_level;
	current_level.push(this->root_);

	//	Run the search
	uint16_t letter = 0;
	std::shared_ptr<TrieNode> current;
	while (letter != word.size()) {
		//	The Depth-Level Queue to load onto for the next iteration
		std::queue<std::shared_ptr<TrieNode>> next_level;
		while (!current_level.empty()) {
			//	Unload the node
			current = current_level.front();
			//	Check for a space
			if (word[letter] == ' ') {
				//	space was found -> Traverse all children
				for (auto itr = current->children.begin(); itr != current->children.end(); itr++) {
					if (itr->first != endSymbol_) {
						//	Push this child onto the queue
						next_level.push(itr->second);
					}
				}
			} else {
				//	no space -> Try the letter of the node's child
				if (current->children.count(word[letter])) {
						//	The letter is in current -> load
						next_level.push(current->children[word[letter]]);
				}
			}
			//	Remove the node
			current_level.pop();
		}
		//	Prepare for the next iteration
		current_level.swap(next_level);
		letter++;
	}

	//	Current level is loaded with nodes to be checked for end
	while (!current_level.empty()) {
		//	Unload the node
		current = current_level.front();
		//	Check it for term
		if (current->children.count(endSymbol_)) {
			//	Add it to the output
			word_list->push_back(current->GetWord());
		}
		//	Remove the node
		current_level.pop();
	}

	//	Sort the output
	std::sort(word_list->begin(), word_list->end());

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

std::unique_ptr<WordList> Trie::PrefixList(const std::string &word) {
	//	Main method for prefix searching
	if (word.size() < 1) return nullptr;

	//	The word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	The Depth-Level Queue to process
	std::queue<std::shared_ptr<TrieNode>> current_level;
	current_level.push(this->root_);

	//	Run the search
	uint16_t letter = 0;
	std::shared_ptr<TrieNode> current;
	while (letter != word.size() && !current_level.empty()) {
		//	The Depth-Level Queue to load onto for the next iteration
		std::queue<std::shared_ptr<TrieNode>> next_level;
		//	Unload the node
		current = current_level.front();
		//	Perform on its children
		//
		if (current->children.count(word[letter])) {
				//	The letter is in current -> load
				next_level.push(current->children[word[letter]]);
		}
		//	Remove the node
		current_level.pop();
		//	Prepare for the next iteration
		current_level.swap(next_level);
		letter++;
	}

	//	Can we traverse to find words?
	if (letter == word.size() && !current_level.empty()) {
		//	Traverse and add all nodes
		while (!current_level.empty()) {
			//	The Depth-Level Queue to load onto for the next iteration
			std::queue<std::shared_ptr<TrieNode>> next_level;
			while (!current_level.empty()) {
				//	Unload the node
				current = current_level.front();
				//	Perform on its children
				//
				//	Traverse every child
				for (auto itr = current->children.begin(); itr != current->children.end(); itr++) {
					if (itr->first == endSymbol_) {
						//	A word was reached -> push it
						word_list->push_back(current->GetWord());
					} else {
						//	Push this child onto the queue
						next_level.push(itr->second);
					}
				}

				//	Remove the node
				current_level.pop();
			}
			//	Prepare for the next iteration
			current_level.swap(next_level);
		}
	}

	//	Sort the output
	std::sort(word_list->begin(), word_list->end());

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

/*
void Trie::PrintChildren() {
	for (auto itr = child_.begin(); itr != child_.end(); ++itr)
		std::cout << itr->first << std::endl;
}
*/

std::unique_ptr<WordList> Trie::SparsePrefix(const std::string &word) {
	//	Main method for prefix searching
	if (word.size() < 1) return nullptr;

	//	The word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	The Depth-Level Queue to process
	std::queue<std::shared_ptr<TrieNode>> current_level;
	current_level.push(this->root_);

	//	Run the search
	uint16_t letter = 0;
	std::shared_ptr<TrieNode> current;
	while (letter != word.size() && !current_level.empty()) {
		//	The Depth-Level Queue to load onto for the next iteration
		std::queue<std::shared_ptr<TrieNode>> next_level;
		while (!current_level.empty()) {
			//	Unload the node
			current = current_level.front();
			//	Check for a space
			if (word[letter] == ' ') {
				//	space was found -> Traverse all children
				for (auto itr = current->children.begin(); itr != current->children.end(); itr++) {
					if (itr->first != endSymbol_) {
						//	Push this child onto the queue
						next_level.push(itr->second);
					}
				}
			} else {
				//	no space -> Try the letter of the node's child
				if (current->children.count(word[letter])) {
						//	The letter is in current -> load
						next_level.push(current->children[word[letter]]);
				}
			}
			//	Remove the node
			current_level.pop();
		}
		//	Prepare for the next iteration
		current_level.swap(next_level);
		letter++;
	}

	//	Can we traverse to find words?
	if (letter == word.size() && !current_level.empty()) {
		//	Traverse and add all nodes
		while (!current_level.empty()) {
		//	The Depth-Level Queue to load onto for the next iteration
			std::queue<std::shared_ptr<TrieNode>> next_level;
			//	Traverse and add all nodes
			while (!current_level.empty()) {
				//	Unload the node
				current = current_level.front();
				//	Perform on its children
				//
				//	Traverse every child
				for (auto itr = current->children.begin(); itr != current->children.end(); itr++) {
					if (itr->first == endSymbol_) {
						//	A word was reached -> push it
						word_list->push_back(current->GetWord());
					} else {
						//	Push this child onto the queue
						next_level.push(itr->second);
					}
				}

				//	Remove the node
				current_level.pop();
			}
			//	Prepare for the next iteration
			current_level.swap(next_level);
		}
	}

	//	Sort the output
	std::sort(word_list->begin(), word_list->end());

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

std::unique_ptr<WordList> Trie::SuffixList(const std::string &word) {
	//	Main method for prefix searching
	if (word.size() < 1) return nullptr;

	//	The word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	The current node to process
	std::shared_ptr<TrieNode> current;
	uint16_t letter = 0;
	auto node_char = node_char_list_.equal_range(word[letter]);
	for (auto itr = node_char.first; itr != node_char.second; itr++) {
		//	Prep for this traverse
		letter = 1;
		current = itr->second;
		//	Traverse this node to the suffixs end
		while (letter != word.size()) {
			if (current->children.count(word[letter])) {
					//	The letter is in current -> load
					current = current->children[word[letter]];
					letter++;
			} else break;
		}

		//	Did we reach the end?
		if (letter == word.size()) {
			//	Push if end is found
			if (current->children.count(endSymbol_)) {
				word_list->push_back(current->GetWord());
			}
		}
	}

	//	Sort the output
	std::sort(word_list->begin(), word_list->end());

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

std::unique_ptr<WordList> Trie::SparseSuffix(const std::string &word) {
	//	Main method for prefix searching
	if (word.size() < 1) return nullptr;

	//	Catch wrong use of sparse
	if (word[0] == ' ') return nullptr;

	//	The word list
	std::unique_ptr<WordList> word_list = std::make_unique<WordList>();

	//	The current node to process
	uint16_t letter = 0;
	auto node_char = node_char_list_.equal_range(word[letter]);
	for (auto itr = node_char.first; itr != node_char.second; itr++) {
		SparseSuffixTraverse(itr->second, word, letter+1, word_list);
	}

	//	Sort the output
	std::sort(word_list->begin(), word_list->end());

	//	Output the result
	if (word_list->size() != 0)
		return (word_list);
	else return nullptr;
}

void Trie::SparseSuffixTraverse(std::shared_ptr<TrieNode> &trienode, const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	//	Check for end of word
	if (letter == word.size()) {
		//	Push if end is found
		if (trienode->children.count(endSymbol_)) {
			word_list->push_back(trienode->GetWord());
		}
		return;
	}

	//	Check for a space
	if (word[letter] == ' ') {
		//	Call traverse on each letter
		for (auto itr = trienode->children.begin(); itr != trienode->children.end(); itr++) {
			if (itr->second != nullptr)
				SparseSuffixTraverse(itr->second, word, letter+1, word_list);
		}
	} else {
		//	Find a letter
		if (trienode->children.count(word[letter])) {
			SparseSuffixTraverse(trienode->children[word[letter]], word, letter+1, word_list);
		}
	}
	return;
}

