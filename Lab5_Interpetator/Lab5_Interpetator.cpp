#include "Interpretator.h"

int main()
{
	//cout << " Input the filename: ";
	//string filename;  cin >> filename;
	//Interpretator inter;
	//float result = inter.interpretate(filename);
	//cout << " The result is: " << result;
	TreeCreator tree;
	tree.parseLine("abc=1");
	tree.parseLine("q=3");
	tree.parseLine("q=2+abc*q");
	tree.outMap();
	return 0;
}

