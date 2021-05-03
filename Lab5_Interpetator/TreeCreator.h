#pragma once
#include "ASTree.h"
#include <map>
#include <stack>
#include <vector>

class TreeCreator
{
	vector<string> operators = { "^", "*", "/", "%", "+", "-", "=", ">", "<", "==", ">=", "<="};
	// part of tree
	stack<Node*> nodes;
	Node* AST;
	map<string, float> variables;
	// 
	stack<string> operatorStack;

	// functions for shuntingYard algorithm
	int getPrecedence(string token);
	bool checkBrackets(string line);
	bool isOperator(string token);
	int isBigger(string token1, string token2);
	string getAssos(string token);
	string whichParenth(string token);

	// functions to create tree
	Node* createNode(string symbol);
	Node* shuntingYard(string line);

	// functions for check condition in if clause
	bool condition(Node* curr);
	
public:
	Node* createTree(vector<string> lines, int& currLine);
	Node* createTree(vector<string> lines);
	float calcResult(Node* root);
	void outMap();
};
