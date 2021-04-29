#pragma once
#include "ASTree.h"
#include <map>
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
	vector<string> operators = { "^", "*", "/", "%", "+", "-", "="};
	stack<Node*> nodes;
	vector<PrecedenceItem> precedence = {{"^", 3 ,"Right"}, {"*", 2,"Left"}, {"/", 2,"Left"},{"%", 2,"Left"}, {"+", 1,"Left"},{"-", 1,"Left"},{"=", 0,"Left"} };
	stack<string> operatorStack;
	stack<string> outputStack;
	map<string, float> variables;
public:
	void parseLine(string line);
	bool isOperator(string token);
	int isBigger(string token1, string token2);
	string getAssos(string token);
	string whichParenth(string token);
	void showTreeTLR(Node* curr, int level);
	float calcResult(Node* root);
	Node* createNode(string symbol);
	void outMap();
};

void outputS(stack<string> stack);