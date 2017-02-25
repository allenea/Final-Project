/*
 * main.cpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#include "movieRecs.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

int main(){
	srand(time(NULL));
	movieRecs mr("MovieList.txt");
	mr.start();
}


