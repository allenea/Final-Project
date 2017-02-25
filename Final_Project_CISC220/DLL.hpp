/*
 * DLL.hpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#ifndef DLL_HPP_
#define DLL_HPP_

#include <stdlib.h>
#include <string>

#include "LLNode.hpp"
#include "TNode.hpp"
using namespace std;

class DLL{
	friend class movieRecs;
	LLNode *first;
	LLNode *last;
	int size;
public:
	DLL();
	~DLL();
	void printDLL();
	void addFirst(string g);
	void addFirst(LLNode *n);
	void push(string g);
	void push(LLNode *n);
	bool search(string t);
	void sort();
};

#endif /* DLL_HPP_ */
