#include "Interpretator.h"

int main()
{
	//cout << " Input the filename: ";
	//string filename;  cin >> filename;
	//Interpretator inter;
	//float result = inter.interpretate(filename);
	//cout << " The result is: " << result;
	TreeCreator tree;
	tree.parseLine("(2.5*4]+2-5.1*3");
	return 0;
}

