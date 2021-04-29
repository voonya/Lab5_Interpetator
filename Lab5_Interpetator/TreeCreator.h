#pragma once
#include "ASTree.h"
#include <stack>
#include <vector>
struct PrecedenceItem {
	char oper;
	int value;
	string associativity;
	PrecedenceItem(char o, int v, string a) : oper(o), value(v), associativity(a) {};
};


class TreeCreator
{
	vector<string> parenth = { '(','{','[',')','}',']' };
	vector<string> operators = { '^', '*', '/', '%', '+', '-'};
	stack<Node*> nodes;
	vector<PrecedenceItem> precedence = {{'^', 2 ,"Right"}, {'*', 1,"Left"}, {'/', 1,"Left"},{'%', 1,"Left"}, {'+', 0,"Left"},{'-', 0,"Left"}};
	//stack<Node> operatorStack;
	//stack<Node> ouputStack;
	stack<char> operatorStack;
	stack<char> outputStack;
public:
	void parseLine(string line);
	bool isOperator(char token);
	int isBigger(char token1, char token2);
	string getAssos(char token);
	string whichParenth(char token);
	void showTreeTLR(Node* curr, int level);
	float calcResult(Node* root);
};

void outputS(stack<char> stack);