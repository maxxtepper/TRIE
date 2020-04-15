#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include "src/lib/TrieNode.h"

int main(int argc, char** argv) {
	std::string pwd;
	char cwd[1024];
	if (getcwd(cwd,sizeof(cwd)) != NULL)
		pwd = cwd;
	else {
		std::cout << "ERROR! Could not find cwd!\n";
		return -1;
	}

	std::string word_file = argv[2];

	TrieNode trie('#');

	std::stringstream ss;
	std::ifstream my_file("dictionary.csv");

	if (my_file.is_open()) {
		std::string line;
		while (std::getline(my_file, line)) {
			std::string word;
			ss << line;
			std::getline(ss,word);
			std::cout << "Adding word: " << word << std::endl;
			trie.AddWord(word);
			ss.clear();
		}
		my_file.close();
	} else {
		std::cout << "Unable to open the file\n";
	}
	
	/*
	std::string input = "1";
	while (input != "0") {
		std::cout << "Add a word (0 to stop): ";
		std::cin >> input;
		if (input != "0")
			std::cout << (bool)trie.AddWord(input) << std::endl;
	}

	input = "1";
	*/

	std::string input = "1";
	while (input != "0") {
		std::cout << "Try a word (0 to quit): ";
		std::cin >> input;
		if (input != "0")
			std::cout << (bool)trie.TryWord(input) << std::endl;
	}

	return 0;
}
