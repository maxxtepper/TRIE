#include <iostream>
#include "src/lib/TrieNode.h"

int main(int argc, char** argv) {
	std::string word_file = argv[2];

	TrieNode trie('#');
	
	std::string input;
	while (input != "0") {
		std::cout << "Add a word(0 to stop): ";
		std::cin >> input;
		std::cout << std::endl;
		if (input != "0")
			std::cout << (bool)trie.AddWord(input) << std::endl;
	}

	input = "1";
	while (input != "0") {
		std::cout << "Try a word(0 to stop): ";
		std::cin >> input;
		std::cout << std::endl;
		if (input != "0")
			std::cout << (bool)trie.TryWord(input) << std::endl;
	}

	return 0;
}
