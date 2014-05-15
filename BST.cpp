#include "BST.h"
#include <string.h> 

using namespace std;

// empty constructor
BST::BST(){
	root = NULL;
}

BinNode *BST::getRoot() {
	return root;
}

// Done by Weronika
void BST::insertNode(string newData){
	// get the files in another method and read each line from it
	// call insert node on each line
	BinNode *newNode = new BinNode(NULL, NULL, newData);
	// if the root is null, set the data of the root to the first thing you read in
	if(root == NULL){
		root = newNode;
		return;
	// else, insert a leaf
	} else { 
		insertAux(newNode, root);
	}
}

// Done by Emily
void BST::insertAux(BinNode *node, BinNode *subTreeRoot){
	if (node->getData().compare(subTreeRoot->getData()) < 0) {
		if (subTreeRoot->getLeft() == NULL) {
			subTreeRoot->setLeft(node);
			return;
		} else {
			insertAux(node, subTreeRoot->getLeft());
		}
	} else if (node->getData().compare(subTreeRoot->getData()) > 0) {
		if (subTreeRoot->getRight() == NULL) {
			subTreeRoot->setRight(node);
			return;
		} else {
			insertAux(node, subTreeRoot->getRight());
		}
	} else {
		return;
	}
}

//Done by Emily
string BST::preorderTraverse(BinNode *node, string & poTraversal){
	if (node) {
		poTraversal += string(node->getData());
		poTraversal += " ";
		if (node->getLeft()) preorderTraverse(node->getLeft(), poTraversal);
		if (node->getRight()) preorderTraverse(node->getRight(), poTraversal);
	}
	return poTraversal;
}

//Done by Emily
string BST::inorderTraverse(BinNode *node, string & ioTraversal){
	if (node) {
		if (node->getLeft()) inorderTraverse(node->getLeft(), ioTraversal);
		ioTraversal += string(node->getData());
		ioTraversal += " ";
		if (node->getRight()) inorderTraverse(node->getRight(), ioTraversal);
	}
	return "";
}

string BST::preorderWalk(int i) {
	string poTraversal = "";
	string preorder = preorderTraverse(this->getRoot(), poTraversal);
	string ithNode = "";
	unsigned pos; // position of (i-1)th whitespace in string
	int whitespaces = 0;
	for (int j = 0; j < poTraversal.length(); j++) {
		if (whitespaces == i-1) {
			pos = unsigned(j);
			j = poTraversal.length();		
		} else {
			if (poTraversal.at(j) == ' ') whitespaces++;
		}
	}
	return poTraversal.substr(pos, 2);
}

string BST::inorderWalk(int i) {
	string ioTraversal = "";
	string inorder = inorderTraverse(this->getRoot(), ioTraversal);
	string ithNode = "";
	unsigned pos; // position of (i-1)th whitespace in string
	int whitespaces = 0;
	for (int j = 0; j < ioTraversal.length(); j++) {
		if (whitespaces == i-1) {
			pos = unsigned(j);
			j = ioTraversal.length();		
		} else {
			if (ioTraversal.at(j) == ' ') whitespaces++;
		}
	}
	return ioTraversal.substr(pos, 2);
}

// Done by Emily
bool BST::isSubTree(BST *secondBST) {
	string firstPreOrder = "";
	string secondPreOrder = "";
	string firstPOWalk = preorderTraverse(this->getRoot(), firstPreOrder);
	string secondPOWalk = preorderTraverse(secondBST->getRoot(), secondPreOrder);

	string firstInOrder = "";
	string secondInOrder = "";
	string firstIOWalk = inorderTraverse(this->getRoot(), firstInOrder);
	string secondIOWalk = inorderTraverse(secondBST->getRoot(), secondInOrder);

	// position of 2nd bst in 1st bst (preorder)
	unsigned pos1 = firstPreOrder.find(secondPreOrder);
	// position of 2nd bst in 1st bst (inorder)
	unsigned pos2 = firstInOrder.find(secondInOrder);

	if (pos1 != 4294967295 && pos2 != 4294967295) return true;
	else return false;
}

// Done by Emily
bool BST::searchBST(string addressIn, BinNode* current) {
	if (current) {
		if (current->getData() == addressIn) {
			return true;
		} else {
			if (current->getLeft() != NULL) {
				searchBST(addressIn, current->getLeft());
			}
			if (current->getRight() != NULL) {
				searchBST(addressIn, current->getRight());
			}
		}
	}
}

// Done by Emily
/*int BST::addIntegers(string address) {
	int total = 0; // total value to be returned
	string currentInt; // current integer between periods
	for (int i = 0; i < address.length(); i++) {
		if (address.at(i) != '.' || i != address.length() - 1) {
			currentInt += address.at(i);
		} else {
			total += int(currentInt);
			currentInt = "";
		}
	}
	return total;	
}*/

//Done by Weronika
//postorder traversal of tree - used by the destructor
void BST::postTraversal(BinNode *node){
	if(node){
		postTraversal(node->getLeft());
		postTraversal(node->getRight());
		delete node;
	}
}

//Done by Weronika
//destructor
//do the postorder traversal
//delete the children before the parent
BST::~BST(){
	if(root == NULL){
	}else{
		postTraversal(root);
	}
}

