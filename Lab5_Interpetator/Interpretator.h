#pragma once
#include "TreeCreator.h"
#include "Reader.h"
#include <iostream>
#include <string>

using namespace std;

class Interpretator
{
	Node* tree;
public:
	float interpretate(string filename);
	void showTreeTLR(Node* curr, int level);
};

