#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <unistd.h>
#include "src/lib/TrieNode.h"

int main(int argc, char** argv) {
	//	Directory handeling
	std::string pwd;
	char cwd[1024];
	if (getcwd(cwd,sizeof(cwd)) != NULL)
		pwd = cwd;
	else {
		std::cout << "ERROR! Could not find cwd!\n";
		return -1;
	}
	std::cout << pwd << std::endl;

	//	Input handeling
	std::string word_file = argv[2];

	//	Data Objects
	TrieNode trie('#',"");

	//	CSV Parsing Setup
	std::stringstream ss;
	std::ifstream my_file("twl2016.csv");

	//	Load the data into the object
	std::cout << "Loading twl2016.csv into the trie..." << std::endl;
	uint64_t word_count = 0;
	if (my_file.is_open()) {
		std::string line;
		while (std::getline(my_file, line)) {
			std::string word;
			ss << line;
			std::getline(ss,word);
			trie.insert(word);
			word_count++;
			ss.clear();
		}
		my_file.clear();
		my_file.seekg(0, std::ios::beg);
	} else {
		std::cout << "Unable to open the file\n";
	}

	//	The count
	std::cout << "Word Count: " << word_count << std::endl;
	std::cout << "Node Count: " << trie.Count() << std::endl;

	//	The Menu
	while(true) {
		std::string mode = "";
		std::cout << "\nWelcome to the Scrabble Trie!\n";
		std::cout << "Pick which mode you would like to play with: \n";
		std::cout << "1. Find Word\n";
		std::cout << "2. Prefix List\n";
		std::cout << "3. Sparse Word List\n";
		std::cout << "4. Sparse Prefix List\n";
		std::cout << "0. Quit\n";
		std::cout << "Choice: ";
		std::cin >> mode;
		std::cout << std::endl;
		int choice = std::stoi(mode);
		switch(choice) {
			case 1:
			{
				std::string input = "";
				//	Recycle the input
				std::getline(std::cin, input);
				while (input != "0") {
					std::cout << "Try a word (0 to quit): ";
					std::getline(std::cin, input);
					if (input != "0") {
						bool isAWord = trie.find(input);
						if (isAWord)
							std::cout << input << " IS a word\n";
						else
							std::cout << input << " is NOT a word\n";
					}
				}
				break;
			}
			case 2:
			{
				std::string input = "";
				//	Recycle the input
				std::getline(std::cin, input);
				while (input != "0") {
					std::cout << "Enter a word (0 to quit): ";
					std::getline(std::cin, input);
					if (input != "0") {
						std::unique_ptr<WordList> word_list = trie.PrefixList(input);
						if (word_list != nullptr) {
							std::for_each(word_list->begin(), word_list->end(), [](std::string i) {
								std::cout << i << std::endl;
							});
							std::cout << "List size = " << word_list->size() << std::endl;
						}
						else
							std::cout << "Empty List!\n";
					}
				}
				break;
			}
			case 3:
			{
				std::string input = "";
				//	Recycle the input
				std::getline(std::cin, input);
				while (input != "0") {
					std::cout << "Enter a sparse word (0 to quit): ";
					std::getline(std::cin, input);
					if (input != "0") {
						std::unique_ptr<WordList> word_list = trie.SparseWord(input);
						if (word_list != nullptr) {
							std::for_each(word_list->begin(), word_list->end(), [](std::string i) {
								std::cout << i << std::endl;
							});
							std::cout << "List size = " << word_list->size() << std::endl;
						}
						else
							std::cout << "Empty List!\n";
					}
				}
				break;
			}
			case 4:
			{
				std::string input = "";
				//	Recycle the input
				std::getline(std::cin, input);
				while (input != "0") {
					std::cout << "Enter a sparse prefix (0 to quit): ";
					std::getline(std::cin, input);
					if (input != "0") {
						std::unique_ptr<WordList> word_list = trie.SparsePrefix(input);
						if (word_list != nullptr) {
							std::for_each(word_list->begin(), word_list->end(), [](std::string i) {
								std::cout << i << std::endl;
							});
							std::cout << "List size = " << word_list->size() << std::endl;
						}
						else
							std::cout << "Empty List!\n";
					}
				}
				break;
			}
			default: break;
		}
		if (choice == 0) break;
	}

	my_file.close();

	return 0;
}
