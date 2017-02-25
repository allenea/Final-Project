/*
 * BST.hpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#ifndef BST_HPP_
#define BST_HPP_

#include "TNode.hpp"
#include <stdlib.h>
#include <string>
using namespace std;

class BST{
	friend class movieRecs;
	friend class LLNode;
	TNode *root;
	int count;
public:
	BST();
	~BST();
	int getHeight(TNode *n);
	int balFac(TNode *n);
	void setHeight(TNode *n);
	TNode *search(int n);
	TNode *search(TNode *r, int n);
	TNode *insert(TNode *r, TNode *n);
	TNode *insert(TNode *n);
	TNode *balance(TNode *n);
	TNode *rotateRight(TNode *n);
	TNode *rotateLeft(TNode *n);
	void printTreeio();
	void printTreeio(TNode *n);
	void printRecs(int t);
	void printRecs(TNode *n, int t);
};



#endif /* BST_HPP_ */
