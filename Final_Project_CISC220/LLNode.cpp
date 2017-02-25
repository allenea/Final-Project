/*
 * Node.cpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#include <stdlib.h>
#include <string>
#include <iostream>

#include "LLNode.hpp"
using namespace std;

/* Constructor sets genre */
LLNode::LLNode(string g){
	genre = g;
	prev = NULL;
	next = NULL;
	tree = new BST();
}

/* Constructor sets genre, title, and rank */
LLNode::LLNode(string g, string t, int r){
	next = NULL;
	prev = NULL;
	genre = g;
	title = t;
	uRating = 0;
	rank = r;
}

LLNode::~LLNode(){
	if (prev != NULL || next != NULL) {
		cout << "deleting this Node may cause a memory leak" << endl;
	}
}


