/*
 * TNode.cpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#include "TNode.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

TNode::TNode(string g, int rnk, string rate, string y, string t){
	genre = g;
	rank = rnk;
	rating = rate;
	year = y;
	title = t;
	left = NULL;
	right = NULL;
	height = 1;
}

TNode::~TNode(){
	if (left != NULL || right != NULL) {
		cout << "deleting this TNode may cause a memory leak" << endl;
	}
}



