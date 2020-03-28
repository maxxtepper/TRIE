#ifndef TRIE_SRC_LIB_ROOT_H_
#define TRIE_SRC_LIB_ROOT_H_

#include <memory>
#include <unordered_map>
#include "Node.h"

class Root : public Node {
	public:
		Root(char n) : Node(n) {}
		~Root();

		virtual char GetChar();
	private:
		std::unordered_map<char,std::unique_ptr<Node>> child_;
};

#endif
