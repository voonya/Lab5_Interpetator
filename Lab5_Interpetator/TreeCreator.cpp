#include "TreeCreator.h"
#include <string>

Node* TreeCreator::createTree(vector<string> lines, int &curr) {
	if (lines[curr].substr(0, 2) == "if") {
		Node* newIf = new Node("if");
		newIf->childs.resize(3);
		newIf->childs[0] = shuntingYard(lines[curr].substr(2, string::npos));
		newIf->childs[1] = new Node("ifBody");
		curr++;
		while (curr < lines.size() && lines[curr] != "endif") {
			newIf->childs[1]->childs.push_back(createTree(lines, curr));
		}
		curr++;
		if (curr < lines.size() && lines[curr] != "else") {
			return newIf;
		}
		curr++;
		Node* elseBody = new Node("elseBody");
		newIf->childs[2] = elseBody;
		while (curr < lines.size() && lines[curr] != "endelse") {
			newIf->childs[2]->childs.push_back(createTree(lines, curr));
		}
		curr++;
		return newIf;
	}
	else {
		return shuntingYard(lines[curr++]);
	}
}

//Node* TreeCreator::createTree(vector<string> lines) {
//	AST = new Node("root");
//	for (int i = 0; i < lines.size(); i++) {
//		string currLine = lines[i];
//		Node* newBranch;
//		if (currLine.find("if") != string::npos) {
//			newBranch = new Node("if");
//			newBranch->childs.resize(3);
//			newBranch->childs[0] = shuntingYard(currLine.substr(currLine.find("if") + 2, string::npos));
//			Node* ifBody = new Node("ifbody");
//			while (lines[++i].find("endif") == string::npos) {
//				ifBody->childs.push_back(shuntingYard(lines[i]));
//			}
//			newBranch->childs[1] = ifBody;
//			if (lines[++i].find("else") != string::npos) {
//				Node* elseBody = new Node("elsebody");
//				while (lines[++i].find("endelse") == string::npos) {
//					elseBody->childs.push_back(shuntingYard(lines[i]));
//				}
//				newBranch->childs[2] = elseBody;
//			}
//		}
//		else {
//			newBranch = shuntingYard(currLine);
//			
//		}
//		AST->childs.push_back(newBranch);
//	}
//	return AST;
//}

Node* TreeCreator::shuntingYard(string line) {
	if (!checkBrackets(line)) { 
		cout << "unmatched brackets found" << endl;
		exit(0);
	}
	for (int i = 0; i < line.length(); i++) {
		string token = line.substr(i, 1);
		if (line[i] == '=' && i == line.length()-1) {
			cout << "Incorrect syntax\n";
			exit(0);
		}
		// process numbers
		if (isdigit(token[0]) || (line[i]=='-' && i > 0 && isOperator(line.substr(i-1, 1))) || (line[i] == '-' && i==0)) {
			while (isdigit(line[i+1]) || line[i+1] == '.') {
				token += line[i+1];
				i++;
			}
			Node* newNode = new Node(token);
			nodes.push(newNode);
		}
		else if (isOperator(token)) {
			if (line.substr(i + 1, 1) == "=") {
				token += line.substr(i + 1, 1);
				i++;
			}
			while ((!operatorStack.empty() && isOperator(operatorStack.top()))
				&& ((isBigger(operatorStack.top(), token) == 1)
					|| (isBigger(operatorStack.top(), token) == 0 && getAssos(token) == "Left")))
			{
				Node* newNode = createNode(operatorStack.top());
				nodes.push(newNode);
				operatorStack.pop();
			}
			operatorStack.push(token);
		}
		else if (whichParenth(token) == "Left") {
			operatorStack.push(token);
		}
		else if (whichParenth(token) == "Right") {
			while (whichParenth(operatorStack.top()) != "Left") {
				nodes.push(createNode(operatorStack.top()));
				operatorStack.pop();
			}
			if (whichParenth(operatorStack.top()) == "Left") {
				operatorStack.pop();
			}
		}
		else {
			string currLex = line.substr(i + 1, 1);
			string varName = token;
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
		}
	}
	while (!operatorStack.empty()) {
		nodes.push(createNode(operatorStack.top()));
		operatorStack.pop();
	}
	return nodes.top();
}

Node* TreeCreator::createNode(string symbol) {
	Node* operatorNode = new Node(symbol);
	Node* operNode1 = nodes.top();
	nodes.pop();
	Node* operNode2 = nodes.top();
	nodes.pop();
	operatorNode->childs.push_back(operNode2);
	operatorNode->childs.push_back(operNode1);
	return operatorNode;
}

float TreeCreator::calcResult(Node* curr) {
	if (curr) {
		double result = 0;
		if (curr->value == "if") {
			if (condition(curr->childs[0])) {
				calcResult(curr->childs[1]);
			}
			else if (curr->childs.size() > 2) {
				calcResult(curr->childs[2]);
			}
		}
		else if (curr->value == "ifBody") {
			for (int i = 0; i < curr->childs.size(); i++) {
				calcResult(curr->childs[i]);
			}
		}
		else if (curr->value == "elseBody") {
			for (int i = 0; i < curr->childs.size(); i++) {
				calcResult(curr->childs[i]);
			}
		}
		else if (curr->childs.size() == 0) {
			if (isdigit((curr->value)[0]) || (curr->value[0] == '-' && isdigit(curr->value[1]))) {
				return stod(curr->value);
			}
			return variables[curr->value];
		}
		else {
			double left = calcResult(curr->childs[0]);
			double right = calcResult(curr->childs[1]);
			if (isOperator(curr->value)) {
				if (curr->value == "*") {
					result = left * right;
				}
				else if (curr->value == "/") {
					result = left / right;
				}
				else if (curr->value == "%") {
					result = int(left) % int(right);
				}
				else if (curr->value == "^") {
					result = pow(left, right);
				}
				else if (curr->value == "-") {
					result = left - right;
				}
				else if (curr->value == "+") {
					result = left + right;
				}
				else if (curr->value == "=") {
					variables[curr->childs[0]->value] = right;
					result = variables[curr->childs[0]->value];
				}
				return result;
			}

		}
	}

}

bool TreeCreator::condition(Node* curr) {
	if (curr->childs.size() == 0) {
		if (isdigit(curr->value[0]) || (curr->value[0] == '-' && isdigit(curr->value[1]))) {
			return stof(curr->value) > 0;
		}
		else {
			return variables[curr->value] > 0;
		}
	}
	else {
		float left = calcResult(curr->childs[0]);
		float right = calcResult(curr->childs[1]);
		if (curr->value == ">") {
			return left > right;
		}
		else if (curr->value == "<") {
			return left < right;
		}
		else if (curr->value == "==") {
			return left == right;
		}
		else if (curr->value == ">=") {
			return left >= right;
		}
		else if (curr->value == "<=") {
			return left <= right;
		}
	}
}


bool TreeCreator::isOperator(string token) {
	for (int i = 0; i < operators.size(); i++) {
		if (token == operators[i]) {
			return true;
		}
	}
	return false;
}

int TreeCreator::getPrecedence(string token){
	if (token == "^") {
		return 4;
	}
	else if (token == "*" || token == "/" || token == "%") {
		return 2;
	}
	else if (token == "+" || token == "-") {
		return 1;
	}
	else if (token == "=" || token == ">" || token == "<" || token == "==" || token == ">=" || token == "<=") {
		return 0;
	}
}

int TreeCreator::isBigger(string token1, string token2) {
	int pre1 = getPrecedence(token1);
	int pre2 = getPrecedence(token2);
	if (pre1 > pre2) return 1;
	if (pre1 == pre2) return 0;
	return -1;
}

string TreeCreator::getAssos(string token) {
	if (token == "^" || token == "=" || token == ">" || token == "<" || token == "==" || token == ">=" || token == "<=") {
		return "Right";
	}
	else if (token == "*" || token == "/" || token == "%" || token == "+" || token == "-") {
		return "Left";
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

void TreeCreator::outMap() {
	for (auto it = variables.begin(); it != variables.end(); it++) {
		cout << (*it).first << ": " << it->second << '\n';
	}
}