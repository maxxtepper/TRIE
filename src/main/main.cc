#include <iostream>
#include "Trie.h"

int main(int argc, char** argv) {
	std::string word_file = argv[2];

	Trie trie(word_file);
	
	char input = NULL;
	while (input != '0') {
		std::cout << "Search: ";
		std::cin >> input;
		std::cout << std::endl;

		std::cout << trie.FindWord(input) << std::endl;
	}

	return 0;
}
