#ifndef TRIE_SRC_LIB_NODE_H_
#define TRIE_SRC_LIB_NODE_H_

class Node {
	public:
		Node(const char n) : val_(n) {}
		virtual ~Node() = default;

		char GetChar() { return val_; }

	private:
		const char val_;

};

#endif
