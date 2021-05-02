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
	vector<string> operators = { "^", "*", "/", "%", "+", "-", "="};
	stack<Node*> nodes;
	Node* AST;
	stack<string> operatorStack;
	stack<string> outputStack;
	map<string, float> variables;
	int getPrecedence(string token);
	bool checkBrackets(string line);
	bool isOperator(string token);
	int isBigger(string token1, string token2);
	float calcResult(Node* root);
	Node* createNode(string symbol);
	string getAssos(string token);
	string whichParenth(string token);
public:
	void parseLine(string line);
	void showTreeTLR(Node* curr, int level);
	void outMap();
};

void outputS(stack<string> stack);