#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <unistd.h>
#include "src/lib/Trie.h"

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
	Trie trie;
	std::vector<std::string> word_list;

	//	CSV Parsing Setup
	std::stringstream ss;
	std::ifstream my_file("twl2016.csv");

	//	Setup timing
	auto start    = std::chrono::high_resolution_clock::now();
	auto stop     = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//	Load the data into the object
	std::cout << "Loading twl2016.csv into the trie..." << std::endl;
	uint64_t word_count = 0;
	start = std::chrono::high_resolution_clock::now();
	if (my_file.is_open()) {
		std::string line;
		while (std::getline(my_file, line)) {
			std::string word;
			ss << line;
			std::getline(ss,word);
			//std::cout << "Adding word: " << word << std::endl;
			trie.insert(word);
			word_count++;
			word_list.push_back(word);
			ss.clear();
		}
		my_file.clear();
		my_file.seekg(0, std::ios::beg);
	} else {
		std::cout << "Unable to open the file\n";
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "The trie loaded in " << duration.count() << " us\n";

	// Check each word in the list
	if (mode == 2) {
	std::cout << "Checking the vector..." << std::endl;
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
			trie.find(word);
			ss.clear();
		}
		my_file.close();
	} else {
		std::cout << "Unable to open the file\n";
	}
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "The trie took " << duration.count() << "us\n";

	std::cout << "Node count = " << trie.Count() << std::endl;

	//	Done with the file
	my_file.close();

	// Get a sparse prefix
	std::cout << "Running SparsePrefix..." << std::endl;
	std::string prefix0 = "t t";
	start = std::chrono::high_resolution_clock::now();
	trie.SparsePrefix(prefix0);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "SparsePrefix for " << prefix0 << " is " << duration.count() << "us\n";

	return 0;
}
