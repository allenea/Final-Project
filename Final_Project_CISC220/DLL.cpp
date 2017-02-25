/*
 * DLL.cpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#include "DLL.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>

#include "LLNode.hpp"
using namespace std;

DLL::DLL(){
	first = NULL;
	last = NULL;
	size = 0;
}

DLL::~DLL() {
	LLNode *tmp = first;
	while (first != NULL) {
		tmp = first->next;
		delete first;
		first = tmp;
		size--;
	}//while
	first = NULL;
	last = NULL;
}

void DLL::printDLL(){
	LLNode *tmp = first;
	while (tmp != NULL) {
		cout << tmp->genre << "->";
		tmp = tmp->next;
	}//while
	cout << endl;
	return;
}

void DLL::addFirst(string g){
	LLNode *node = new LLNode(g);
	first = node;
	last = node;
	size++;
	return;
}

void DLL::addFirst(LLNode *n){
	first = n;
	last = n;
	size++;
	return;
}

void DLL::push(string g){
	if(first == NULL){
		addFirst(g);
		return;
	}//if
	LLNode *node = new LLNode(g);
	last->next = node;
	node->prev = last;
	last = node;
	size++;
	return;
}

void DLL::push(LLNode *n){
	if(first == NULL){
		addFirst(n);
		return;
	}//if
	last->next = n;
	n->prev = last;
	last = n;
	size++;
	return;
}

bool DLL::search(string t){
	LLNode *tmp = first;
	while(tmp != NULL){
		if(tmp->title == t){
			return true;
		}//if
		tmp = tmp->next;
	}//while
	return false;
}

void DLL::sort(){
	LLNode *curr = first; // current slot
	LLNode *tmp; // moving through list
	LLNode *max; // max
	for(int i = 0; i < size; i++){
		tmp = curr;
		max = curr;
		for(int j = 0; j < size - i; j++){
			if(tmp->uRating > max->uRating){
				max = tmp;
			}//if
			tmp = tmp->next;
		}//for j
		int tmpRate = curr->uRating;
		curr->uRating = max->uRating;
		max->uRating = tmpRate;

		string tmpGenre = curr->genre;
		curr->genre = max->genre;
		max->genre = tmpGenre;

		string tmpTitle = curr->title;
		curr->title = max->title;
		max->title = tmpTitle;

		int tmpRank = curr->rank;
		curr->rank = max->rank;
		max->rank = tmpRank;

		curr = curr->next;
	}//for i
}
