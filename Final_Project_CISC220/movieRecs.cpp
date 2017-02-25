/*
 * movieRecs.cpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#include "movieRecs.hpp"
#include "DLL.hpp"
#include "LLNode.hpp"
#include "TNode.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

movieRecs::movieRecs(string infile) {
	database = new DLL;
	userRated = new DLL;
	loadDatabase(infile);
}

/* Parses the movie text file and loads into database
 *
 * Parameter: string infile (name of txt file)
 * no return
 */
void movieRecs::loadDatabase(string infile) {
	ifstream file(infile.c_str(), ios::in);
	if (!file.is_open()) {
		return;
	}
	int i = 0;
	string line;
	string del = "|";
	string tmp = "";
	while (getline(file, line)) {
		// Parsing each line into separate components
		string genre = line.substr(0, line.find(del));
		line = line.erase(0, line.find(del) + 1);

		string rnk = line.substr(0, line.find(del));
		int rank = atoi(rnk.c_str());
		line = line.erase(0, line.find(del) + 1);

		string rating = line.substr(0, line.find(del));
		line = line.erase(0, line.find(del) + 1);

		string year = line.substr(0, line.find(del));
		line = line.erase(0, line.find(del) + 1);

		string title = line;
		TNode *node = new TNode(genre, rank, rating, year, title);
		if (genre != tmp) {
			database->push(genre);
			database->last->tree->insert(node);
		} else {
			database->last->tree->insert(node);
		} //if/else
		  //database->first->tree->printTreeio();
		tmp = genre;
		i++;
	}		//while
	return;
}

/* Starts the movie recommendation program and loops until exit
 *
 * no parameters or return
 */
void movieRecs::start() {
	string response;
	while (true) {
		rec();
		cout << "Enter 1 to continue. Enter 0 to exit." << endl;
		cin >> response;
		if (response == "0") {
			cout << "Thank you for using the movie recommendation tool!"
					<< endl;
			break;
		}
		userRated = new DLL;
	}
}

/* Runs recommendation portion of program. Asks user for genres, asks user to rate random
 * movies from chosen genres, and picks similar movies based on ratings.
 *
 * no paramters or return
 */
void movieRecs::rec() {
	string response;
	cout
			<< "Please choose three genres from the list below (Enter the numbers of the genres separated by spaces)"
			<< endl;
	LLNode *tmp = database->first;
	int i = 1;
	while (tmp != NULL) {
		cout << i << ": " << tmp->genre << endl;
		i++;
		tmp = tmp->next;
	}
	// obtaining string of genre numbers
	getline(cin, response);

	getRecs(response); // Creating linked list of movies to be rated based on genres
	cout << endl;
	cout
			<< "Rate the following movies on a scale of 1-10 (only enter integers, 10 is highest)"
			<< endl;
	cout << "Enter 0 (zero) to skip a movie" << endl << endl;

	tmp = userRated->first;
	int x;
	int y = 0;
	string response2;

	//Having user rate 10 movies, adds more if user skips a movie
	while (y < 10) {
		cout << tmp->title << endl;
		cin >> response2;
		x = atoi(response2.c_str());
		if (x == 0) {
			addRec(response);
			tmp->uRating = x;
			tmp = tmp->next;
			continue;
		} //if
		tmp->uRating = x;
		tmp = tmp->next;
		y++;
	} //while

	userRated->sort(); //sorting based on user rating (high to low)

	cout << "Based on your ratings, you may like:" << endl;
	tmp = userRated->first;
	while (tmp != NULL) {
		// Don't get recommendation if user skipped
		if (tmp->uRating == 0) {
			tmp = tmp->next;
			continue;
		} //if
		LLNode *tmp2 = database->first;
		while (tmp2 != NULL) {
			// Going to genre node in database
			if (tmp2->genre == tmp->genre) {
				break;
			} //if
			tmp2 = tmp2->next;
		} //while tmp2
		  // Printing recommendations
		tmp2->tree->printRecs(tmp->rank);
		tmp = tmp->next;
	}		//while tmp
	return;
}

/* Creates a linked list of random movies from chosen genres for user to rate
 *
 * Parameter: string s (user chosen genres)
 * no return
 */
void movieRecs::getRecs(string s) {
	int *nums;
	nums = parseInput(s);
	int j = 0;

	while (true) {
		int randNum = rand() % 100 + 1;
		int genreNum = nums[j % 3];

		LLNode *tmp1 = database->first;
		//looping through database DLL to get to correct genre node
		for (int i = 0; i < genreNum - 1; i++) {
			tmp1 = tmp1->next;
		}		//for

				// Obtaining random node from genre tree
		TNode *tmp2 = tmp1->tree->search(randNum);
		// Inserting node into list of nodes to be rated if movie isn't already in list
		if (!(userRated->search(tmp2->title))) {
			LLNode *tmp3 = new LLNode(tmp2->genre, tmp2->title, tmp2->rank);
			userRated->push(tmp3);
		}		//if

		// Breaking if list of movies to be rated has 10 movies
		if (userRated->size == 10) {
			break;
		}		//if
		j++;
		//userRated->printDLL();
	}		//while
	return;
}

/* Adds single random movie to list of movies to be rated.
 * Works the same as getRecs() but loops until a single movie is added.
 *
 * Parameter: string s (user chosen genres)
 * no return
 */
void movieRecs::addRec(string s) {
	int *nums;
	nums = parseInput(s);
	while (true) {
		int randNum = rand() % 100 + 1;
		int genreNum = nums[rand() % 3];

		LLNode *tmp1 = database->first;

		for (int i = 0; i < genreNum - 1; i++) {
			tmp1 = tmp1->next;
		}
		TNode *tmp2 = tmp1->tree->search(randNum);
		if (!(userRated->search(tmp2->title))) {
			LLNode *tmp3 = new LLNode(tmp2->genre, tmp2->title, tmp2->rank);
			userRated->push(tmp3);
			return;
		}
	} //while-continues until movie is added
	return;
}

/* Parses user input to extract genres
 *
 * Parameter: string s (string of user chosen genres)
 * returns array of genre numbers
 */
int *movieRecs::parseInput(string s) {
	int *nodeNums = new int[3];
	string del = " ";
	string num = s.substr(0, s.find(del));
	int x = atoi(num.c_str());
	s = s.erase(0, s.find(del) + 1);
	nodeNums[0] = x;
	num = s.substr(0, s.find(del));
	x = atoi(num.c_str());
	s = s.erase(0, s.find(del) + 1);
	nodeNums[1] = x;
	x = atoi(s.c_str());
	nodeNums[2] = x;
	return &nodeNums[0];
}
