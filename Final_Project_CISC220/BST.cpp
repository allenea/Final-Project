/*
 * BST.cpp

 * Matt Meyers (section 40)
 * Eric Allen (section 41)
 * TA: Leighanne Hsu
 */

#include "BST.hpp"
#include "TNode.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

BST::BST() {
	root = NULL;
	count = 0;
}

BST::~BST() {

}

/* Gives the height of a node in a tree
 *
 * Parameter: TNode *n - node in question
 * returns the height (int)
 */
int BST::getHeight(TNode *n) {
	if (n == NULL) {
		return 0;
	} else {
		return n->height;
	}//if
}

/* Gives the balance factor of a node in a tree
 *
 * Parameter: TNode *n - node in question
 * returns the balance factor (int)
 */
int BST::balFac(TNode *n) {
	return (getHeight(n->left) - getHeight(n->right));
}

/*Sets the height of a node to be one greater than the max height of its children
 *
 * Parameter:	NodeTB n
 * no return
 */
void BST::setHeight(TNode *n) {
	int lHeight = getHeight(n->left);
	int rHeight = getHeight(n->right);
	if (lHeight > rHeight) {
		n->height = lHeight + 1;
	} else {
		n->height = rHeight + 1;
	}//if
}

/*Recursively inserts a TNode into an AVL tree
 *
 * Parameters:	TNode *n - node being inserted
 * returns the root node
 */
TNode *BST::insert(TNode *n) {
	if (root == NULL) {
		root = n;
		count++;
		return root;
	}//if
	if (n->rank < root->rank) {
		root->left = insert(root->left, n);
	} else {
		root->right = insert(root->right, n);
	}//if/else
	count++;
	root = balance(root);
	return root;

}

/*Continuation of previous function
 *
 * Parameters:	TNode *r (root of subtree)
 * 				TNode *n (node being inserted)
 * returns the root node
 */
TNode *BST::insert(TNode *r, TNode *n) {
	if (r == NULL) {
		return n;
	}
	if (n->rank < r->rank) {
		r->left = insert(r->left, n);
	} else {
		r->right = insert(r->right, n);
	}
	return balance(r);
}

/*Performs rotations to balance a tree
 *
 * Parameters: TNode *n (root of tree)
 * returns root node
 */
TNode *BST::balance(TNode *n) {
	setHeight(n);
	TNode *tmp = n;
	if (balFac(n) <= -2) {
		if (balFac(n->right) > 0) {
			n->right = rotateRight(n->right);
		} //if >0
		tmp = rotateLeft(n);
	} else if (balFac(n) >= 2) {
		if (balFac(n->left) < 0) {
			n->left = rotateLeft(n->left);
		} //if <0
		tmp = rotateRight(n);
	} //if 2/-2
	return tmp;
}

/*Performs a right rotation around the root node n
 *
 * Parameters:	TNode *n (root of tree being rotated)
 * Returns root of new tree
 */
TNode *BST::rotateRight(TNode *n) {
	TNode *x = n->left;
	TNode *tmp = x->right;

	x->right = n;
	n->left = tmp;
	setHeight(n);
	setHeight(x);
	return x;
}

/*Performs a left rotation around the root node n
 *
 * Parameters:	TNode n (root of tree being rotated)
 * Returns root of new tree
 */
TNode *BST::rotateLeft(TNode *n) {
	TNode *x = n->right;
	TNode *tmp = x->left;

	x->left = n;
	n->right = tmp;
	setHeight(n);
	setHeight(x);
	return x;
}

/*Recursively prints a tree in order
 *
 * no parameters or return
 */
void BST::printTreeio() {
	if (root == NULL) {
		return;
	}
	//cout << "GOING LEFT" << endl;
	printTreeio(root->left);
	//cout << "BACK" << endl;
	cout << root->rank << ": " << root->title << endl;
	//cout << "GOING RIGHT" << endl;
	printTreeio(root->right);
	return;
}

/*Recursively prints a tree in order
 *
 * Parameters:	TNode n (root of subtree)
 * no return
 */
void BST::printTreeio(TNode *n) {
	//cout << "IN LEFT" << endl;
	if (n == NULL) {
		return;
	}
	printTreeio(n->left);
	cout << n->rank << ": " << n->title << endl;
	printTreeio(n->right);
	return;
}

/* Recursively searches a tree the node with a certain rank
 *
 * Parameter: int n (rank in question)
 * returns node with rank n
 */
TNode *BST::search(int n) {
	if (root->rank == n) {
		return root;
	}
	if (n < root->rank) {
		return search(root->left, n);
	} else {
		return search(root->right, n);
	}

}

/* Recursively searches a tree the node with a certain rank
 *
 * Parameter: int n (rank in question)
 * 			  TNode *r (root of subtree)
 * returns node with rank n
 */
TNode *BST::search(TNode *r, int n) {
	if (r == NULL) {
		return NULL;
	}
	if (r->rank == n) {
		return r;
	}
	if (n < r->rank) {
		return search(r->left, n);
	} else {
		return search(r->right, n);
	}
}

/* Recursively find node of rank t and print recommendations
 *
 * Parameter: int t (rank of user rated movie)
 * no return
 */
void BST::printRecs(int t) {
	if (root->rank == t) {
		cout << "Title: " << root->left->title << endl;
		cout << "Genre: " << root->left->genre << endl;
		cout << "Year: " << root->left->year << endl;
		cout << "Rotten Tomatoes Rating: " << root->left->rating << endl;
		cout << endl;
		cout << "Title: " << root->right->title << endl;
		cout << "Genre: " << root->right->genre << endl;
		cout << "Year: " << root->right->year << endl;
		cout << "Rotten Tomatoes Rating: " << root->right->rating << endl;
		cout << endl;
		return;
	}
	if (t < root->rank) {
		return printRecs(root->left, t);
	} else {
		return printRecs(root->right, t);
	}
}

/* Recursively find node of rank t and print recommendations
 *
 * Parameter: int t (rank of user rated movie)
 * 			  TNode *n (root of subtree)
 * no return
 */
void BST::printRecs(TNode *n, int t) {
	if (n->rank == t) {
		if (n->left != NULL) {
			cout << "Title: " << n->left->title << endl;
			cout << "Genre: " << n->left->genre << endl;
			cout << "Year: " << n->left->year << endl;
			cout << "Rotten Tomatoes Rating: " << root->left->rating << endl;
			cout << endl;
		}
		if (n->right != NULL) {
			cout << "Title: " << n->right->title << endl;
			cout << "Genre: " << n->right->genre << endl;
			cout << "Year: " << n->right->year << endl;
			cout << "Rotten Tomatoes Rating: " << n->right->rating << endl;
			cout << endl;
		}
		return;
	}
	if (t < n->rank) {
		return printRecs(n->left, t);
	} else {
		return printRecs(n->right, t);
	}
}
