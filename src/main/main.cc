#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <unistd.h>
#include "src/lib/TrieNode.h

int main(int argc, char** argv) {
	std::string pwd;
	char cwd[1024];
	if (getcwd(cwd,sizeof(cwd)) != NULL)
		pwd = cwd;
	else {
		std::cout << "ERROR! Could not find cwd!\n";
		return -1;
	}
	std::cout << pwd << std::endl;

	std::string word_file = argv[2];

	TrieNode trie('#');
//	std::vector<std::string> word_list;

	std::stringstream ss;
	std::ifstream my_file("twl2016.csv");

	//	The Load
	std::cout << "Loading twl2016.csv into the trie..." << std::endl;
	uint64_t word_count = 0;
	if (my_file.is_open()) {
		std::string line;
		while (std::getline(my_file, line)) {
			std::string word;
			ss << line;
			std::getline(ss,word);
			//std::cout << "Adding word: " << word << std::endl;
			trie.AddWord(word);
			word_count++;
//			word_list.push_back(word);
			ss.clear();
		}
		my_file.clear();
		my_file.seekg(0, std::ios::beg);
	} else {
		std::cout << "Unable to open the file\n";
	}

	/*
	// Check each word in the list
	auto start = std::chrono::high_resolution_clock::now();
	if (my_file.is_open()) {
		std::string line;
		while (std::getline(my_file, line)) {
			std::string word;
			ss << line;
			std::getline(ss,word);
	//		std::find(word_list.begin(), word_list.end(), word);
			ss.clear();
		}
		my_file.clear();
		my_file.seekg(0, std::ios::beg);
	} else {
		std::cout << "Unable to open the file\n";
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "The vector took " << duration.count() << " us\n";
	
	start = std::chrono::high_resolution_clock::now();
	// Check each word in the trie
	if (my_file.is_open()) {
		std::string line;
		while (std::getline(my_file, line)) {
			std::string word;
			ss << line;
			std::getline(ss,word);
			trie.TryWord(word);
			ss.clear();
		}
		my_file.close();
	} else {
		std::cout << "Unable to open the file\n";
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "The trie took " << duration.count() << "us\n";
	
	std::string input = "1";
	while (input != "0") {
		std::cout << "Add a word (0 to stop): ";
		std::cin >> input;
		if (input != "0")
			std::cout << (bool)trie.AddWord(input) << std::endl;
	}

	std::string input = "1";
	*/

	//	The count
	std::cout << "Word Count: " << word_count << std::endl;
	std::cout << "Node Count: " << trie.Count() << std::endl;

	std::string input = "1";
	while (input != "0") {
		std::cout << "Try a word (0 to quit): ";
		std::cin >> input;
		if (input != "0") {
			bool isAWord = trie.TryWord(input);
			if (isAWord)
				std::cout << input << " IS a word\n";
			else
				std::cout << input << " is NOT a word\n";
		}
	}

	my_file.close();

	return 0;
}
