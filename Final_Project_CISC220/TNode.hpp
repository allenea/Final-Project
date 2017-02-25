/*
 * TNode.hpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#ifndef TNODE_HPP_
#define TNODE_HPP_

#include <stdlib.h>
#include <string>
using namespace std;

class TNode{
	friend class BST;
	friend class movieRecs;
	TNode *left;
	TNode *right;
	string genre;
	int rank;
	string rating;
	string year;
	string title;
	int height;
public:
	TNode(string g, int rnk, string rate, string y, string t);
	~TNode();
};



#endif /* TNODE_HPP_ */
