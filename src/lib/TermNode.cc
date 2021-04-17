#include "TermNode.h"

bool TermNode::TryAddLetters(const std::string &word, uint16_t letter) {
	return true;
}

bool TermNode::AddLetters(const std::string &word, uint16_t letter) {
	return true;
}

bool TermNode::TryLetters(const std::string &word, uint16_t letter) {
	return true;
}

bool TermNode::TryPrefix(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	return true;
}

bool TermNode::GetWords(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	return true;
}

void TermNode::TrySparseWord(const std::string &word, uint16_t letter, std::unique_ptr<WordList> &word_list) {
	return;
}
