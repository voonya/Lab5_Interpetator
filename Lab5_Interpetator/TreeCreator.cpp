#include "TreeCreator.h"
#include <string>
void TreeCreator::parseLine(string line) {

	for (int i = 0; i < line.length(); i++) {
		string token = line.substr(i,1);
		if (isdigit(token[0])) {
			outputStack.push(token);
			Node* newNode = new Node(token);
			nodes.push(newNode);
		}
		else if (isOperator(token)) {
			while ((!operatorStack.empty() && isOperator(operatorStack.top())) && ((isBigger(operatorStack.top(), token) == 1)
				|| (isBigger(operatorStack.top(), token) == 0 && getAssos(token) == "Left")) && (whichParenth(token) != "Left"))
			{
				cout << "Out oper: " << operatorStack.top() << endl;
				Node* operNode2 = nodes.top();
				nodes.pop();
				Node* operNode1 = nodes.top();
				nodes.pop();
				Node* operatorNode = new Node(operatorStack.top());
				operatorNode->left = operNode1;
				operatorNode->right = operNode2;
				outputStack.push(operatorStack.top());
				operatorStack.pop();
				nodes.push(operatorNode);
			}
			operatorStack.push(token);
		}
		else if (whichParenth(token) == "Left") {
			operatorStack.push(token);
		}
		else if (whichParenth(token) == "Right") {
			while (whichParenth(operatorStack.top()) != "Left") {
				cout << "Out oper: " << operatorStack.top() << endl ;
				Node* operNode2 = nodes.top();
				nodes.pop();
				Node* operNode1 = nodes.top();
				nodes.pop();
				Node* operatorNode = new Node(operatorStack.top());
				operatorNode->left = operNode1;
				operatorNode->right = operNode2;
				outputStack.push(operatorStack.top());
				operatorStack.pop();
				nodes.push(operatorNode);
			}
			if (whichParenth(operatorStack.top()) == "Left") {
				operatorStack.pop();
			}
			// if for function
		}
		cout << "Output: ";
		outputS(outputStack);
		cout << "Operator: ";
		outputS(operatorStack);
	}
	while (!operatorStack.empty()) {
		cout << "Out oper: " << operatorStack.top() << endl;
		Node* operNode2 = nodes.top();
		nodes.pop();
		Node* operNode1 = nodes.top();
		nodes.pop();
		Node* operatorNode = new Node(operatorStack.top());
		operatorNode->left = operNode1;
		operatorNode->right = operNode2;
		outputStack.push(operatorStack.top());
		operatorStack.pop();
		nodes.push(operatorNode);
	}
	string output = "";
	while (!outputStack.empty()) {
		output =  outputStack.top() + output;
		outputStack.pop();
	}
	cout << output << endl;
	showTreeTLR(nodes.top(), 0);
	cout << "Result: " << calcResult(nodes.top());
}

bool TreeCreator::isOperator(char token) {
	for (int i = 0; i < operators.size(); i++) {
		if (token == operators[i]) {
			return true;
		}
	}
	return false;
}
int TreeCreator::isBigger(char token1, char token2) {
	int pre1, pre2;
	for (int i = 0; i < precedence.size(); i++) {
		if (precedence[i].oper == token1) pre1 = precedence[i].value;
		if (precedence[i].oper == token2) pre2 = precedence[i].value;
	}
	if (pre1 > pre2) return 1;
	if (pre1 == pre2) return 0;
	return -1;
}
string TreeCreator::getAssos(char token) {
	for (int i = 0; i < precedence.size(); i++) {
		if (token == precedence[i].oper) {
			return precedence[i].associativity;
		}
	}
	return "";
}
string TreeCreator::whichParenth(char token) {
	if (strcmp(&token, "(") == 0 || strcmp(&token, "{") == 0 || strcmp(&token, "[") == 0) {
		return "Left";
	}
	else if (strcmp(&token, ")") == 0 || strcmp(&token, "}") == 0 || strcmp(&token, "]") == 0) {
		return "Right";
	}
	return "";
}

void outputS(stack<char> s) {
	stack<char> copy = s;
	while (!copy.empty()) {
		cout << copy.top();
		copy.pop();
	}
	cout << endl;
}

void TreeCreator::showTreeTLR(Node* curr, int level) {
	if (curr)
	{
		for (int i = 0; i < level; i++) cout << char(179) << "    ";
		cout << char(192) << char(196) << curr->value << endl;
		showTreeTLR(curr->left, level + 1);
		showTreeTLR(curr->right, level + 1);
	}
}

float TreeCreator::calcResult(Node* curr) {
	if (curr) {
		float left = calcResult(curr->left);

		float right = calcResult(curr->right);
		if (isOperator(curr->value)) {
			cout << left << " " << curr->value << " " << right << "\n";
			if (curr->value == '*') {
				return left * right;
			}
			else if (curr->value == '/') {
				return left / right;
			}
			else if (curr->value == '%') {
				return int(left) % int(right);
			}
			else if (curr->value == '^') {
				return pow(left, right);
			}
			else if (curr->value == '-') {
				return left - right;
			}
			else if (curr->value == '+') {
				return left - right;
			}
		}
		if (curr->left == NULL && curr->right == NULL && isdigit(curr->value)) {
			cout << curr->value  << " " << static_cast <float>(curr->value) << endl;
			return static_cast <float>(curr->value);
		}
	}

}