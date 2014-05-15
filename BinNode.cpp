#include "BinNode.h"

//Done by Weronika.
BinNode::BinNode(){
	left = NULL;
	right = NULL;
	data = "";
}

BinNode::BinNode(BinNode *leftIn, BinNode *rightIn, string dataIn) {
	left = leftIn;
	right = rightIn;
	data = dataIn;
}

BinNode* BinNode::getLeft(){
	return left;
}

BinNode* BinNode::getRight(){
	return right;
}

void BinNode::setLeft(BinNode *leftIn){
	left = leftIn;
}

void BinNode::setRight(BinNode *rightIn){
	right = rightIn;
}

string BinNode::getData(){
	return data;
}

BinNode::~BinNode(){
}
