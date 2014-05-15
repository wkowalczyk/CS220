#ifndef BST_H__
#define BST_H__

#include <iostream>
#include <string>
#include "BinNode.h"

class BST {

	private:
		BinNode *root;

	public:
		//empty constructor
		BST();
		BinNode *getRoot();
		void insertNode(string newData);
		void insertAux(BinNode *node, BinNode *subTreeRoot);
		string preorderTraverse(BinNode *node, string & poTraversal);
		string inorderTraverse(BinNode *node, string & ioTraversal);
		string preorderWalk(int i);
		string inorderWalk(int i);
		void postTraversal(BinNode *node);
		bool isSubTree(BST *secondBST);
		bool searchBST(string addressIn, BinNode* current);
		//int addIntegers(string address);
		//destructor
		~BST();

};

#endif
