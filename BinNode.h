#ifndef BIN_NODE_H__
#define BIN_NODE_H__

#include <iostream>
#include <string>

using namespace std;

//Done by Weronika.
class BinNode {

	private:
		BinNode *left;
		BinNode *right;
		std::string data;

	public:
		//empty constructor
		BinNode();
		//explicit value constructor
		BinNode(BinNode *leftIn, BinNode *rightIn, string dataIn);
		BinNode *getLeft();
		BinNode *getRight();
		void setLeft(BinNode *leftIn);
		void setRight(BinNode *rightIn);
		std::string getData();
		//destructor
		~BinNode();

};

#endif
