#pragma once
#include "ASTree.h"
#include <stack>
#include <vector>
struct PrecedenceItem {
	string oper;
	int value;
	string associativity;
	PrecedenceItem(string o, int v, string a) : oper(o), value(v), associativity(a) {};
};


class TreeCreator
{
	vector<string> parenth = { "(","{","[",")","}","]" };
	vector<string> operators = { "^", "*", "/", "%", "+", "-"};
	stack<Node*> nodes;
	vector<PrecedenceItem> precedence = {{"^", 2 ,"Right"}, {"*", 1,"Left"}, {"/", 1,"Left"},{"%", 1,"Left"}, {"+", 0,"Left"},{"-", 0,"Left"}};
	stack<string> operatorStack;
	stack<string> outputStack;
public:
	void parseLine(string line);
	bool isOperator(string token);
	int isBigger(string token1, string token2);
	string getAssos(string token);
	string whichParenth(string token);
	void showTreeTLR(Node* curr, int level);
	float calcResult(Node* root);
	Node* createNode(string symbol);
};

void outputS(stack<string> stack);