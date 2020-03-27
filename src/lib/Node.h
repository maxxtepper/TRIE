#ifndef TRIE_SRC_LIB_NODE_H_
#define TRIE_SRC_LIB_NODE_H_

class Node {
	public:
		virtual Node(const char n) : nval_(n) {}
		virtual ~Node() = default;

		virtual GetChar() { return nval_; }

	private:
		char nval_;

};

#endif
