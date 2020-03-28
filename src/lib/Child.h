#ifndef TRIE_SRC_LIB_CHILD_H_
#define TRIE_SRC_LIB_CHILD_H_

#include <memory>
#include <unordered_map>
#include "Node.h"

class Child {
	public:
		Child();
		~Child();

	private:
		std::unordered_map<char,std::unique_ptr<Node>> child_;
};

#endif
