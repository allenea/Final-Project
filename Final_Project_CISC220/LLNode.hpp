/*
 * Node.hpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#ifndef LLNODE_HPP_
#define LLNODE_HPP_

#include "BST.hpp"
#include <stdlib.h>
#include <string>
using namespace std;

class LLNode{
	friend class DLL;
	friend class movieRecs;
	LLNode *prev;
	LLNode *next;
	string genre;
	BST *tree;
	int rank;
	int uRating;
	string rating;
	string year;
	string title;
public:
	LLNode(string g);
	LLNode(string g, string t, int r);
	~LLNode();
};



#endif /* LLNODE_HPP_ */
