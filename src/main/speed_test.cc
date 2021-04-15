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
	//std::string word_file = argv[2];
	if (argc < 2) {
		std::cout << "./test_case mode\n";
		return 0;
	}
	int mode = std::stoi(argv[1]);

	//	Data Objects
	TrieNode trie('#',"");
	std::vector<std::string> word_list;

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
			//std::cout << "Adding word: " << word << std::endl;
			trie.AddWord(word);
			word_count++;
			word_list.push_back(word);
			ss.clear();
		}
		my_file.clear();
		my_file.seekg(0, std::ios::beg);
	} else {
		std::cout << "Unable to open the file\n";
	}

	//	Setup timing
	auto start    = std::chrono::high_resolution_clock::now();
	auto stop     = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	// Check each word in the list
	std::cout << "Checking the vector..." << std::endl;
	if (mode == 2) {
		start = std::chrono::high_resolution_clock::now();
		if (my_file.is_open()) {
			std::string line;
			while (std::getline(my_file, line)) {
				std::string word;
				ss << line;
				std::getline(ss,word);
				std::find(word_list.begin(), word_list.end(), word);
				ss.clear();
			}
			my_file.clear();
			my_file.seekg(0, std::ios::beg);
		} else {
			std::cout << "Unable to open the file\n";
		}
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "The vector took " << duration.count() << " us\n";
	}
	
	// Check each word in the trie
	std::cout << "Checking the trie..." << std::endl;
	start = std::chrono::high_resolution_clock::now();
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
	
	my_file.close();

	return 0;
}
