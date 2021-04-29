#include "TreeCreator.h"
#include <string>
/*
TODO: добавить проверку на кол-во скобок в выражении.
FIX: что-то неправвильно выводит результат, хотя вроде считает правильно


*/

bool TreeCreator::checkBrackets(string line) {
	int numberOfBrackets = 0;

	for (size_t position = 0; position < line.length(); position++) {
		string tocken = line.substr(position, 1);
		string check = whichParenth(tocken);
		if (check == "Left") numberOfBrackets++;
		else if (check == "Right") numberOfBrackets--;
	}

	bool res = numberOfBrackets == 0 ? true : false;
	return res;
}

void TreeCreator::parseLine(string line) {
	if (!checkBrackets(line)) { 
		cout << "unmatched brackets found" << endl;
		return;
	}

	for (int i = 0; i < line.length(); i++) {
		string token = line.substr(i, 1);
		if (isdigit(token[0])) {
			string currLex = line.substr(i + 1, 1);
			while (isdigit(currLex[0]) || currLex == ".") {
				token += currLex;
				i++;
				currLex = line.substr(i + 1, 1);
			}
			outputStack.push(token);
			Node* newNode = new Node(token);
			nodes.push(newNode);
		}
		else if (isOperator(token)) {
			while ((!operatorStack.empty() && isOperator(operatorStack.top()))
				&& ((isBigger(operatorStack.top(), token) == 1)
					|| (isBigger(operatorStack.top(), token) == 0 && getAssos(token) == "Left")))
			{
				cout << "Out oper: " << operatorStack.top() << endl;
				Node* newNode = createNode(operatorStack.top());
				nodes.push(newNode);
				outputStack.push(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.push(token);
		}
		else if (whichParenth(token) == "Left") {
			operatorStack.push(token);
		}
		else if (whichParenth(token) == "Right") {
			while (whichParenth(operatorStack.top()) != "Left") {
				cout << "Out oper: " << operatorStack.top() << endl;
				nodes.push(createNode(operatorStack.top()));
				outputStack.push(operatorStack.top());
				operatorStack.pop();
			}
			if (whichParenth(operatorStack.top()) == "Left") {
				operatorStack.pop();
			}
			// if-clause for function
		}
		else {
			string currLex = line.substr(i + 1, 1);
			string varName = token;
			string num = "";
			while (!isdigit(currLex[0]) && currLex != "."  && !isOperator(currLex) && whichParenth(currLex) == "") {
				varName += currLex;
				i++;
				if (i < line.length() - 1) {
					currLex = line.substr(i + 1, 1);
				}
				else {
					break;
				}
			}
			Node* newNode = new Node(varName);
			nodes.push(newNode);
			outputStack.push(varName);
		}
		cout << "Output: ";
		outputS(outputStack);
		cout << "Operator: ";
		outputS(operatorStack);
	}
	while (!operatorStack.empty()) {
		cout << "Out oper: " << operatorStack.top() << endl;
		nodes.push(createNode(operatorStack.top()));
		outputStack.push(operatorStack.top());
		operatorStack.pop();
	}
	string output = "";
	while (!outputStack.empty()) {
		output =  outputStack.top() + output;
		outputStack.pop();
	}
	cout << output << endl;
	showTreeTLR(nodes.top(), 0);
	cout << "Result: " << calcResult(nodes.top()) << endl;
}

bool TreeCreator::isOperator(string token) {
	for (int i = 0; i < operators.size(); i++) {
		if (token == operators[i]) {
			return true;
		}
	}
	return false;
}
int TreeCreator::isBigger(string token1, string token2) {
	int pre1, pre2;
	for (int i = 0; i < precedence.size(); i++) {
		if (precedence[i].oper == token1) pre1 = precedence[i].value;
		if (precedence[i].oper == token2) pre2 = precedence[i].value;
	}
	if (pre1 > pre2) return 1;
	if (pre1 == pre2) return 0;
	return -1;
}
string TreeCreator::getAssos(string token) {
	for (int i = 0; i < precedence.size(); i++) {
		if (token == precedence[i].oper) {
			return precedence[i].associativity;
		}
	}
	return "";
}

string TreeCreator::whichParenth(string token) {
	if (token == "(" || token == "{"|| token == "[" ) {
		return "Left";
	}
	else if (token == ")" || token == "}" || token == "]") {
		return "Right";
	}
	return "";
}

void outputS(stack<string> s) {
	stack<string> copy = s;
	while (!copy.empty()) {
		cout << copy.top();
		copy.pop();
	}
	cout << endl;
}

void TreeCreator::showTreeTLR(Node* curr, int level) {
	if (curr)
	{
		for (int i = 0; i < level; i++) cout << char(179) << "   ";
		cout << char(192) << char(196) << curr->value << endl;
		showTreeTLR(curr->left, level + 1);
		showTreeTLR(curr->right, level + 1);
	}
}

float TreeCreator::calcResult(Node* curr) {
	if (curr) {
		double left = calcResult(curr->left);
		double right = calcResult(curr->right);
		if (isOperator(curr->value)) {
			cout << left << " " << curr->value << " " << right << "\n";
			if (curr->value == "*") {
				return left * right;
			}
			else if (curr->value == "/") {
				return left / right;
			}
			else if (curr->value == "%") {
				return int(left) % int(right);
			}
			else if (curr->value == "^") {
				return pow(left, right);
			}
			else if (curr->value == "-") {
				return left - right;
			}
			else if (curr->value == "+") {
				return left + right;
			}
			else if (curr->value == "=") {
				variables[curr->left->value] = right;
				return variables[curr->left->value];
			}
		}
		if (curr->left == NULL && curr->right == NULL) {
			if (isdigit((curr->value)[0])) {
				cout << curr->value << endl;
				return stod(curr->value);
			}
			cout << curr->value << endl;
			return variables[curr->value];
		}
	}

}

Node* TreeCreator::createNode(string symbol) {
	Node* operatorNode = new Node(symbol);
	Node* operNode1 = nodes.top();
	nodes.pop();
	Node* operNode2 = nodes.top();
	nodes.pop();
	operatorNode->left = operNode2;
	operatorNode->right = operNode1;
	return operatorNode;
}

void TreeCreator::outMap() {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		cout << (*it).first << ": " << it->second << '\n';
	}
		

}