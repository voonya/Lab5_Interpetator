#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Node {
	/*Node* left;
	Node* right;
	Node* condition;*/
	vector<Node*> childs;
	string value;
	Node(string value) : value(value){};
	void addChild(Node* node) { this->childs.push_back(node); }
};

class ASTree
{
public:
	vector<Node*> branches;
};

