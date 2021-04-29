#pragma once
#include "TreeCreator.h"
#include "Processor.h"
#include <iostream>
#include <string>
using namespace std;

class Interpretator
{
	ASTree tree;
public:
	float interpretate(string filename);
};

