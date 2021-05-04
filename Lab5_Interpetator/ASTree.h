#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Node {
	vector<Node*> childs;
	string value;
	Node(string value) : value(value){};
};

