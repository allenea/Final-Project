/*
 * movieRecs.hpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#ifndef MOVIERECS_HPP_
#define MOVIERECS_HPP_

#include "DLL.hpp"
#include <stdlib.h>
#include <string>

#include "LLNode.hpp"
using namespace std;

class movieRecs{
	DLL *database;
	DLL *userRated;
public:
	movieRecs(string infile);
	void loadDatabase(string infile);
	void start();
	void rec();
	void getRecs(string s);
	void addRec(string s);
	int *parseInput(string s);
};



#endif /* MOVIERECS_HPP_ */
