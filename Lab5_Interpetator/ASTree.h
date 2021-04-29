#pragma once
#include <iostream>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	string value;
	Node(string value) : value(value), left(NULL), right(NULL) {};
};

class ASTree
{
	Node* root;
public:
	ASTree() : root(NULL) {};
};
