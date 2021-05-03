#include "Interpretator.h"


float Interpretator::interpretate(string filename) {
	Reader reader(filename);
	vector<string> lines = reader.readFile();
	TreeCreator creator;
	tree = creator.createTree(lines);
	showTreeTLR(tree,0);
	float result = 0;
	for (int i = 0; i < tree->childs.size(); i++) {
		result = creator.calcResult(tree->childs[i]);
	}
	creator.outMap();
	return result;
}



void Interpretator::showTreeTLR(Node* curr, int level) {
	if (curr)
	{
		for (int i = 0; i < level; i++) cout << char(179) << "   ";
		cout << char(192) << char(196) << curr->value << endl;
		for (int i = 0; i < curr->childs.size(); i++) {
			showTreeTLR(curr->childs[i], level + 1);
		}
	}
}