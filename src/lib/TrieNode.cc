#include "TrieNode.h"

virtual char TrieNode::TryChar(char letter) {
	if (child_.count(letter))
		return true;
	else
		return false;
}
